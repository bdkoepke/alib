#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "hashtable.h"
#include "node.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
  Hash h;
  Node **array;
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
  return h->h->array[h->i];
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

static inline void _hashtable_insert(Hashtable *h, void *x) {
  size_t hash = h->h(x) % h->capacity;
  node_insert(&h->array[hash], x);
}

static void hashtable_free(Object *o) {
  free(((Hashtable *)o)->array);
  free(o);
}

static void *hashtable_search(const Container *c, const void *x) {
  contract_requires(x != NULL);

  Hashtable *h = (Hashtable *)c;
  size_t hash = h->h(x) % h->capacity;
  return (h->array[hash] == NULL) ? NULL : node_search(h->array[hash], x);
}

static void hashtable_insert(Container *c, void *x) {
  inline void hashtable_resize(Hashtable * h, size_t capacity) {
    contract_requires(h != NULL && h->size < capacity < SIZE_MAX);
    Node **array = h->array;
    size_t _capacity = h->capacity;
    h->capacity = capacity;
    h->array = calloc(capacity, sizeof(Node *));
    size_t i;
    for (i = 0; i < _capacity; i++)
      if (array[i] != NULL) {
        Node *n;
        for (n = array[i]; n != NULL; n = n->n)
          _hashtable_insert(h, n->x);
        node_free_r(n);
      }
    free(array);
  }

  Hashtable *h = (Hashtable *)c;
  contract_requires(x != NULL && h->size < SIZE_MAX);

  if (h->size >= h->capacity) {
    size_t capacity = checked_product(h->capacity, 2, SIZE_MAX);
    hashtable_resize(h, capacity);
    h->capacity = capacity;
  }
  h->size++;
  _hashtable_insert(h, x);
}

static void hashtable_delete(Container *c, const void *x) {
  Hashtable *h = (Hashtable *)c;
  h->size--;
  size_t hash = h->h(x) % h->capacity;
  contract_weak_requires(h->array[hash]);
  node_delete(&(h->array[hash]), x);
}

static bool hashtable_empty(const Container *c) {
  return ((Hashtable *)c)->size == 0;
}

Container *hashtable_new(Hash hash) {
  static container_vtable vtable = {
    { {.free = hashtable_free }, .iterator = hashtable_iterator },
          .search = hashtable_search, .empty = hashtable_empty,
        .delete = hashtable_delete, .insert = hashtable_insert
  };

  static const float DEFAULT_FACTOR = 0.75;
  static const size_t DEFAULT_CAPACITY = 11;

  Hashtable *h = malloc(sizeof(Hashtable));
  h->vtable = &vtable;
  h->h = hash;
  h->capacity = DEFAULT_CAPACITY;
  h->array = calloc(h->capacity, sizeof(Node *));
  h->size = 0;
  h->factor = DEFAULT_FACTOR;
  return (Container *)h;
}
