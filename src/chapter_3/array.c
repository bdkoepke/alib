#include "array.h"
#include "../contract.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  array_vtable *vtable;
  void **array;
  size_t capacity;
  size_t size;
} _Array;

static const int DEFAULT_CAPACITY = 11;

static inline size_t max(size_t a, size_t b) { return a > b ? a : b; }

static inline size_t checked_product(size_t multiplicand, size_t multiplier,
                                     size_t _default) {
  size_t product = multiplicand * multiplier;
  return product < multiplicand ? _default : product;
}

static void shift_right(void **a, size_t length, size_t offset, size_t x) {
  size_t i;
  for (i = offset; i < (length - x); i++)
    a[i] = a[i + x];
}

static inline void array_resize(_Array *a, size_t capacity) {
  contract_requires(a->size < capacity);
  a->array = realloc(a->array, capacity);
}

static void _array_set(Array *a, size_t i, void *x) {
  ((_Array *)a)->array[i] = x;
}

static void *_array_get(const Array *a, size_t i) {
  return ((const _Array *)a)->array[i];
}

static size_t _array_size(const Array *a) { return ((const _Array *)a)->size; }

static void _array_insert(Container *_a, void *x) {
  _Array *a = (_Array *)_a;
  if (array_size((Array *)a) >= a->capacity) {
    size_t new_size =
        checked_product(a->capacity * sizeof(void *), 2, SIZE_MAX);
    array_resize(a, new_size);
    a->capacity = new_size / sizeof(void *);
  }
  size_t size = a->size;
  a->size++;
  array_set((Array *)a, size, x);
}

static inline size_t array_indexof(Array *a, const void *x) {
  size_t i;
  size_t size = array_size(a);
  for (i = 0; i < size; i++)
    if (array_get(a, i) == x)
      return i;
}

static void array_delete(Container *c, const void *x) {
  Array *a = (Array *)c;
  _Array *_a = (_Array *)a;
  size_t size = array_size(a);
  size_t _capacity = max(_a->capacity * 0.33, DEFAULT_CAPACITY);
  if (size < _capacity) {
    array_resize(_a, _capacity * sizeof(void *));
    _a->capacity = _capacity;
  }
  void **array = _a->array;
  shift_right(array, size, array_indexof(a, x), 1);
  _a->size--;
}

static void array_free(Object *a) {
  free(((_Array *)a)->array);
  free(a);
}

Array *array_new() {
  static array_vtable vtable = {
    { {.free = array_free },
          .search = _array_search, .insert = _array_insert,
          .delete = array_delete, .empty = _array_empty },
        .set = _array_set, .get = _array_get, .size = _array_size
  };

  _Array *a = malloc(sizeof(_Array));
  a->vtable = &vtable;
  a->capacity = DEFAULT_CAPACITY;
  a->array = malloc(sizeof(void *) * a->capacity);
  a->size = 0;
  return (Array *)a;
}

size_t array_size(const Array *a) {
  contract_requires(a != NULL);
  return a->vtable->size(a);
}

void array_set(Array *a, size_t i, void *x) {
  contract_requires(a != NULL && i < array_size(a));
  a->vtable->set(a, i, x);
}

void *array_get(const Array *a, size_t i) {
  contract_requires(a != NULL && i < array_size(a));
  return a->vtable->get(a, i);
}

void *_array_search(const Container *c, const void *x) {
  const Array *a = (const Array *)c;
  size_t i;
  size_t size = array_size(a);
  for (i = 0; i < size; i++) {
    void *_x = array_get(a, i);
    if (_x == x)
      return _x;
  }
  return NULL;
}

bool _array_empty(const Container *c) {
  return array_size((const Array *)c) == 0;
}
