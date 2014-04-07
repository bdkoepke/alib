#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "array_list.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  array_list_vtable *vtable;
  void **array;
  size_t capacity;
  size_t size;
} _ArrayList;

typedef struct {
  iterator_vtable *vtable;
  ArrayList *a;
  size_t i;
} ArrayListIterator;

static const int DEFAULT_CAPACITY = 11;

static void *array_list_iterator_current(const Iterator *i) {
  const ArrayListIterator *a = (const ArrayListIterator *)i;
  return array_list_get(a->a, a->i);
}

static bool array_list_iterator_move_next(Iterator *i) {
  ArrayListIterator *a = (ArrayListIterator *)i;
  a->i++;
  if (a->i < array_list_size(a->a))
    return true;
  i->vtable = &iterator_vtable_invalid_state;
  return false;
}

static bool array_list_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .move_next = array_list_iterator_move_next,
                                 .current = array_list_iterator_current
  };

  ArrayListIterator *a = (ArrayListIterator *)i;
  if (container_empty((Container *)a->a)) {
    a->vtable = &iterator_vtable_invalid_state;
    return false;
  }
  a->vtable = &vtable;
  return true;
}

Iterator *array_list_iterator(const Iterable *i) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .move_next = array_list_iterator_move_next_init,
                                 .current = _iterator_current_invalid_state
  };
  ArrayListIterator *a = malloc(sizeof(ArrayListIterator));
  a->vtable = &vtable;
  a->a = (ArrayList *)i;
  a->i = 0;
  return (Iterator *)a;
}

static inline void array_list_resize(_ArrayList *a, size_t capacity) {
  contract_requires(a->size < capacity);
  a->array = realloc(a->array, capacity);
}

static void _array_list_set(ArrayList *a, size_t i, void *x) {
  ((_ArrayList *)a)->array[i] = x;
}

static void *_array_list_get(const ArrayList *a, size_t i) {
  return ((const _ArrayList *)a)->array[i];
}

static size_t _array_list_size(const ArrayList *a) {
  return ((const _ArrayList *)a)->size;
}

static void _array_list_insert(Container *_a, void *x) {
  _ArrayList *a = (_ArrayList *)_a;
  if (array_list_size((ArrayList *)a) >= a->capacity) {
    size_t new_size =
        checked_product(a->capacity * sizeof(void *), 2, SIZE_MAX);
    array_list_resize(a, new_size);
    a->capacity = new_size / sizeof(void *);
  }
  size_t size = a->size;
  a->size++;
  array_list_set((ArrayList *)a, size, x);
}

static void *array_list_delete(Container *c, const void *x) {
  inline void shift_right(void * *a, size_t length, size_t offset, size_t x) {
    size_t i;
    for (i = offset; i < (length - x); i++)
      a[i] = a[i + x];
  }
  inline size_t array_list_indexof(ArrayList * a, const void * x) {
    size_t i;
    size_t size = array_list_size(a);
    for (i = 0; i < size; i++)
      if (array_list_get(a, i) == x)
        return i;
  }
  inline size_t max(size_t a, size_t b) { return a > b ? a : b; }

  ArrayList *a = (ArrayList *)c;
  _ArrayList *_a = (_ArrayList *)a;
  size_t size = array_list_size(a);
  size_t _capacity = max(_a->capacity * 0.33, DEFAULT_CAPACITY);
  if (size < _capacity) {
    array_list_resize(_a, _capacity * sizeof(void *));
    _a->capacity = _capacity;
  }
  void **array = _a->array;
  size_t i = array_list_indexof(a, x);
  void *o = array[i];
  shift_right(array, size, i, 1);
  _a->size--;
  return o;
}

static void array_list_free(Object *a) {
  free(((_ArrayList *)a)->array);
  free(a);
}

ArrayList *array_list_new() {
  static array_list_vtable vtable = {
    { { {.free = array_list_free }, .iterator = array_list_iterator },
          .search = _array_list_search, .empty = _array_list_empty,
          .insert = _array_list_insert, .delete = array_list_delete },
        .set = _array_list_set, .get = _array_list_get, .size = _array_list_size
  };

  _ArrayList *a = malloc(sizeof(_ArrayList));
  a->vtable = &vtable;
  a->capacity = DEFAULT_CAPACITY;
  a->array = malloc(sizeof(void *) * a->capacity);
  a->size = 0;
  return (ArrayList *)a;
}

size_t array_list_size(const ArrayList *a) {
  contract_requires(a != NULL);
  return a->vtable->size(a);
}

void array_list_set(ArrayList *a, size_t i, void *x) {
  contract_requires(a != NULL && i < array_list_size(a));
  a->vtable->set(a, i, x);
}

void *array_list_get(const ArrayList *a, size_t i) {
  contract_requires(a != NULL && i < array_list_size(a));
  return a->vtable->get(a, i);
}

void *_array_list_search(const Container *c, const void *x) {
  const ArrayList *a = (const ArrayList *)c;
  size_t i;
  size_t size = array_list_size(a);
  for (i = 0; i < size; i++) {
    void *_x = array_list_get(a, i);
    if (_x == x)
      return _x;
  }
  return NULL;
}

bool _array_list_empty(const Container *c) {
  return array_list_size((const ArrayList *)c) == 0;
}
