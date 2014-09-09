#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "../lang/unsafe.h"
#include "hashtable.h"
#include "hnode.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  dictionary_vtable *vtable;
  Hash h;
  Equals e;
  HNode **array;
  size_t capacity, size;
  float factor;
} Hashtable;

typedef struct {
  iterator_vtable *vtable;
  Hashtable *h;
  size_t i;
  HNode *n;
} HashtableIterator;

static iterator_vtable vtable_invalid_state = {
  { .class = { "hashtable_iterator" },
    .free = _object_free,
    .to_string = _object_to_string },
  .current = _iterator_current_invalid_state,
  .move_next = _iterator_move_next_invalid_state
};

static void *hashtable_iterator_current(const Iterator *i) {
  HashtableIterator *h = (HashtableIterator *)i;
  return void_cast(h->n->p.k);
}

static bool hashtable_iterator_move_next(Iterator *_i) {
  HashtableIterator *i = (HashtableIterator *)_i;
  Hashtable *h = i->h;
  if (i->n != NULL && (i->n = i->n->n))
    return true;
  for (i->i++; i->i < h->capacity && h->array[i->i] == NULL; i->i++)
    continue;
  if (i->i == h->capacity || h->array[i->i] == NULL)
    return i->vtable = &vtable_invalid_state, false;
  return i->n = h->array[i->i], true;
}

static bool hashtable_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = { { .class = { "hashtable_iterator" },
                                      .free = _object_free,
                                      .to_string = _object_to_string },
                                    .current = hashtable_iterator_current,
                                    .move_next = hashtable_iterator_move_next };
  HashtableIterator *h = (HashtableIterator *)i;
  if (set_empty((Set *)h->h))
    return i->vtable = &vtable_invalid_state, false;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
  return i->vtable = &vtable, hashtable_iterator_move_next(i);
#pragma clang diagnostic pop
}

static Iterator *hashtable_iterator(const Iterable *i) {
  static iterator_vtable vtable = { { .class = { "hashtable_iterator" },
                                      .free = _object_free,
                                      .to_string = _object_to_string },
                                    .current = _iterator_current_invalid_state,
                                    .move_next =
                                        hashtable_iterator_move_next_init };

  HashtableIterator *h = malloc(sizeof(HashtableIterator));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
  h->vtable = &vtable;
#pragma clang diagnostic pop
  h->h = (Hashtable *)i;
  h->i = 0;
  h->n = NULL;
  return (Iterator *)h;
}

static void hashtable_free(Object *o) {
  Hashtable *h = (Hashtable *)o;
  size_t i;
  for (i = 0; i < h->capacity; i++)
    if (h->array[i] != NULL)
      hnode_free_r(h->array[i]);
  free(h->array);
  free(o);
}

static void *hashtable_search(const Dictionary *d, const void *k) {
  Hashtable *h = (Hashtable *)d;
  size_t hash = h->h(k) % h->capacity;
  if (h->array[hash] == NULL)
    return NULL;
  KeyValuePair *p = hnode_search(h->array[hash], k, h->e);
  return p == NULL ? NULL : p->v;
}

static void _hashtable_insert(Hashtable *h, const void *k, void *v) {
  size_t hash = h->h(k) % h->capacity;
  hnode_insert(&(h->array[hash]), k, v);
}

static void hashtable_resize(Hashtable *h, size_t capacity) {
  contract_requires_non_null(h);
  contract_requires(h->size < capacity < SIZE_MAX);
  HNode **array = h->array;
  size_t _capacity = h->capacity;
  h->capacity = capacity;
  h->array = calloc(capacity, sizeof(HNode *));
  size_t i;
  for (i = 0; i < _capacity; i++)
    if (array[i] != NULL) {
      HNode *n;
      for (n = array[i]; n != NULL; n = n->n)
        _hashtable_insert(h, n->p.k, n->p.v);
      hnode_free_r(array[i]);
    }
  free(array);
}

static void hashtable_insert(Dictionary *d, const void *k, void *v) {
  Hashtable *h = (Hashtable *)d;
  contract_requires_non_null(k);
  contract_requires(h->size < SIZE_MAX);
  if (h->size >= h->capacity) {
    size_t capacity = checked_product(h->capacity, 2, SIZE_MAX);
    hashtable_resize(h, capacity);
    h->capacity = capacity;
  }
  h->size++;
  _hashtable_insert(h, k, v);
}

static void *hashtable_reassign(Dictionary *d, const void *k, void *v) {
  Hashtable *h = (Hashtable *)d;
  size_t hash = h->h(k) % h->capacity;
  KeyValuePair *p = hnode_search(h->array[hash], k, h->e);
  void *_v = p->v;
  p->v = v;
  return _v;
}

static void *hashtable_delete(Dictionary *d, const void *k) {
  Hashtable *h = (Hashtable *)d;
  h->size--;
  size_t hash = h->h(k) % h->capacity;
  return hnode_delete(&(h->array[hash]), k, h->e);
}

static bool hashtable_empty(const Set *s) {
  return ((Hashtable *)s)->size == 0;
}

Dictionary *hashtable_new(Hash hash, Equals equals) {
  static dictionary_vtable vtable = {
    { { { .class = { "hashtable" },
          .free = hashtable_free,
          .to_string = _object_to_string },
        .iterator = hashtable_iterator },
      .insert = _dictionary_set_insert, .search = _dictionary_set_search,
      .delete = _dictionary_set_delete, .empty = hashtable_empty },
    .search = hashtable_search, .delete = hashtable_delete,
    .insert = hashtable_insert, .reassign = hashtable_reassign
  };

  static const float DEFAULT_FACTOR = 0.75;
  static const size_t DEFAULT_CAPACITY = 11;

  Hashtable *h = malloc(sizeof(Hashtable));
  h->h = contract_requires_non_null(hash);
  h->e = contract_requires_non_null(equals);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
  h->vtable = &vtable;
#pragma clang diagnostic pop
  h->capacity = DEFAULT_CAPACITY;
  h->array = calloc(h->capacity, sizeof(HNode *));
  h->size = 0;
  h->factor = DEFAULT_FACTOR;
  return (Dictionary *)h;
}
