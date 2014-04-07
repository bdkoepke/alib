#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "hashtable.h"
#include "hnode.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  dictionary_vtable *vtable;
  Hash h;
  HNode **array;
  size_t capacity;
  size_t size;
  float factor;
} Hashtable;

typedef struct {
  iterator_vtable *vtable;
  Hashtable *h;
  size_t i;
} HashtableIterator;

static void *hashtable_iterator_current(const Iterator *i) {
  HashtableIterator *h = (HashtableIterator *)i;
  return h->h->array[h->i]->p.v;
}

static bool hashtable_iterator_move_next(Iterator *_i) {
  HashtableIterator *i = (HashtableIterator *)_i;
  Hashtable *h = (Hashtable *)i->h;
  for (; h->array[i->i] == NULL && i->i < h->capacity; i->i++)
    continue;
  if (h->array[i->i] == NULL) {
    i->vtable = &iterator_vtable_invalid_state;
    return false;
  }
  return true;
}

static bool hashtable_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .current = hashtable_iterator_current,
                                 .move_next = hashtable_iterator_move_next
  };

  HashtableIterator *h = (HashtableIterator *)i;
  if (container_empty((Container *)h->h)) {
    i->vtable = &iterator_vtable_invalid_state;
    return false;
  }
  i->vtable = &vtable;
  return hashtable_iterator_move_next(i);
}

static Iterator *hashtable_iterator(const Iterable *i) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .current = _iterator_current_invalid_state,
                                 .move_next = hashtable_iterator_move_next_init
  };

  HashtableIterator *h = malloc(sizeof(HashtableIterator));
  h->vtable = &vtable;
  h->h = (Hashtable *)i;
  h->i = 0;
  return (Iterator *)h;
}

static void hashtable_free(Object *o) {
  free(((Hashtable *)o)->array);
  free(o);
}

static void *hashtable_search(const Container *c, const void *x) {
  contract_requires(x != NULL);
  Hashtable *h = (Hashtable *)c;
  size_t hash = h->h(x) % h->capacity;
  if (h->array[hash] == NULL)
    return NULL;
  KeyValuePair *p = hnode_search(h->array[hash], x);
  return p == NULL ? NULL : p->v;
}

static void hashtable_insert(Dictionary *d, const void *k, void *v) {
  inline void _hashtable_insert(Hashtable * h, const void * k, void * v) {
    size_t hash = h->h(k) % h->capacity;
    hnode_insert(&(h->array[hash]), k, v);
  }
  inline void hashtable_resize(Hashtable * h, size_t capacity) {
    contract_requires(h != NULL && h->size < capacity < SIZE_MAX);
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
        hnode_free_r(n);
      }
    free(array);
  }
  Hashtable *h = (Hashtable *)d;
  contract_requires(k != NULL && h->size < SIZE_MAX);
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
  KeyValuePair *p = hnode_search(h->array[hash], k);
  void *_v = p->v;
  p->v = v;
  return _v;
}

static void *hashtable_delete(Container *c, const void *k) {
  Hashtable *h = (Hashtable *)c;
  h->size--;
  size_t hash = h->h(k) % h->capacity;
  contract_weak_requires(h->array[hash]);
  return hnode_delete(&(h->array[hash]), k);
}

static bool hashtable_empty(const Container *c) {
  return ((Hashtable *)c)->size == 0;
}

Dictionary *hashtable_new(Hash hash) {
  static dictionary_vtable vtable = {
    { { {.free = hashtable_free }, .iterator = hashtable_iterator },
          .search = hashtable_search, .empty = hashtable_empty,
          .delete = hashtable_delete, .insert = _container_insert },
        .insert = hashtable_insert, .reassign = hashtable_reassign
  };

  static const float DEFAULT_FACTOR = 0.75;
  static const size_t DEFAULT_CAPACITY = 11;

  Hashtable *h = malloc(sizeof(Hashtable));
  h->vtable = &vtable;
  h->h = hash;
  h->capacity = DEFAULT_CAPACITY;
  h->array = calloc(h->capacity, sizeof(HNode *));
  h->size = 0;
  h->factor = DEFAULT_FACTOR;
  return (Dictionary *)h;
}
