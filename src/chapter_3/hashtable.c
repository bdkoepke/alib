#include "../contract.h"
#include "hashtable.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
  Hash h;
  void **array;
  size_t capacity;
  size_t size;
  float factor;
} Hashtable;

static inline size_t checked_product(size_t multiplicand, size_t multiplier,
                                     size_t _default) {
  size_t product = multiplicand * multiplier;
  return product < multiplicand ? _default : product;
}

static inline void _hashtable_insert(Hashtable *h, void *x) {
  size_t hash = h->h(x) % h->capacity;
  size_t i;
  for (i = hash; i < h->capacity; i++)
    if (h->array[i] == NULL) {
      h->array[i] = x;
      h->size++;
      return;
    }
  for (i = 0; i < hash; i++)
    if (h->array[i] == NULL) {
      h->array[i] = x;
      h->size++;
      return;
    }
  assert(false);
}

static inline void hashtable_resize(Hashtable *h, size_t capacity) {
  contract_requires(h != NULL && h->size < capacity < SIZE_MAX);
  void **array = h->array;
  size_t _capacity = h->capacity;
  h->capacity = capacity;
  h->array = calloc(capacity, sizeof(void *));
  size_t i;
  for (i = 0; i < _capacity; i++)
    if (array[i] != NULL)
      _hashtable_insert(h, array[i]);
  free(array);
}

static void hashtable_free(Object *o) {
  free(((Hashtable *)o)->array);
  free(o);
}

static void *hashtable_search(const Container *c, const void *x) {
  contract_requires(x != NULL);

  Hashtable *h = (Hashtable *)c;
  size_t hash = h->h(x) % h->capacity;
  size_t i;
  for (i = hash; i < h->capacity; i++)
    if (h->array[i] == NULL)
      return NULL;
    else if (h->array[i] == x)
      return h->array[i];
  for (i = 0; i < hash; i++)
    if (h->array[i] == NULL)
      return NULL;
    else if (h->array[i] == x)
      return h->array[i];

  return NULL;
}

static void hashtable_insert(Container *c, void *x) {
  Hashtable *h = (Hashtable *)c;
  contract_requires(x != NULL && h->size < SIZE_MAX);

  if (h->size > h->capacity) {
    size_t capacity = checked_product(h->capacity, 2, SIZE_MAX);
    hashtable_resize(h, capacity);
    h->capacity = capacity;
  }
  _hashtable_insert(h, x);
}

static void hashtable_delete(Container *c, const void *x) {
  contract_requires(x != NULL);
  Hashtable *h = (Hashtable *)c;
  size_t hash = h->h(x) % h->capacity;
  size_t i;
  for (i = hash; i < h->capacity; i++)
    if (h->array[i] == x)
      h->array[i] = NULL;
  for (i = 0; i < hash; i++)
    if (h->array[i] == x)
      h->array[i] = NULL;
  assert(false);
}

static bool hashtable_empty(const Container *c) {
  return ((Hashtable *)c)->size == 0;
}

Container *hashtable_new(Hash h) {
  static container_vtable vtable = {
    {.free = hashtable_free },
        .search = hashtable_search, .insert = hashtable_insert,
        .delete = hashtable_delete, .empty = hashtable_empty
  };

  static const float DEFAULT_FACTOR = 0.75;
  static const size_t DEFAULT_CAPACITY = 11;

  Hashtable *hashtable = malloc(sizeof(Hashtable));
  hashtable->vtable = &vtable;
  hashtable->h = h;
  hashtable->capacity = DEFAULT_CAPACITY;
  hashtable->array = calloc(DEFAULT_CAPACITY, sizeof(void *));
  hashtable->size = 0;
  hashtable->factor = DEFAULT_FACTOR;
  return (Container *)hashtable;
}
