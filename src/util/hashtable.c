#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "hashtable.h"
#include "node.h"

#include <assert.h>
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
  assert(h->array[hash]);
  node_delete(&(h->array[hash]), x);
}

static bool hashtable_empty(const Container *c) {
  return ((Hashtable *)c)->size == 0;
}

Container *hashtable_new(Hash hash) {
  static container_vtable vtable = {
    {.free = hashtable_free },
        .search = hashtable_search, .insert = hashtable_insert,
        .delete = hashtable_delete, .empty = hashtable_empty
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
