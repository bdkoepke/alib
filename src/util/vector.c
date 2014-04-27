#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "vector.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  vector_vtable *vtable;
  void **array;
  size_t capacity;
  size_t size;
} _Vector;

typedef struct {
  iterator_vtable *vtable;
  Vector *a;
  size_t i;
} VectorIterator;

static iterator_vtable vtable_invalid_state = {
  { .class = "vector_iterator",
    .free = _object_free,
    .to_string = _object_to_string },
  .current = _iterator_current_invalid_state,
  .move_next = _iterator_move_next_invalid_state
};

static const int DEFAULT_CAPACITY = 11;

static void *vector_iterator_current(const Iterator *i) {
  return vector_get(((VectorIterator *)i)->a, ((VectorIterator *)i)->i);
}

static bool vector_iterator_move_next(Iterator *i) {
  VectorIterator *v = (VectorIterator *)i;
  v->i++;
  if (v->i < vector_size(v->a))
    return true;
  v->vtable = &vtable_invalid_state;
  return false;
}

static bool vector_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = { { .class = "vector_iterator",
                                      .free = _object_free,
                                      .to_string = _object_to_string },
                                    .move_next = vector_iterator_move_next,
                                    .current = vector_iterator_current };

  VectorIterator *v = (VectorIterator *)i;
  if (container_empty((Container *)v->a)) {
    v->vtable = &vtable_invalid_state;
    return false;
  }
  v->vtable = &vtable;
  return true;
}

Iterator *_vector_iterator(const Iterable *i) {
  static iterator_vtable vtable = { { .class = "vector_iterator",
                                      .free = _object_free,
                                      .to_string = _object_to_string },
                                    .move_next = vector_iterator_move_next_init,
                                    .current =
                                        _iterator_current_invalid_state };
  VectorIterator *v = malloc(sizeof(VectorIterator));
  v->vtable = &vtable;
  v->a = (Vector *)i;
  v->i = 0;
  return (Iterator *)v;
}

static inline void vector_resize(_Vector *v, size_t capacity) {
  contract_requires(v->size < capacity);
  v->array = realloc(v->array, capacity);
}

static void _vector_set(Vector *v, size_t i, void *x) {
  ((_Vector *)v)->array[i] = x;
}

static void *_vector_get(const Vector *v, size_t i) {
  return ((const _Vector *)v)->array[i];
}

static size_t _vector_size(const Vector *v) {
  return ((const _Vector *)v)->size;
}

static void _vector_insert(Container *c, void *x) {
  _Vector *v = (_Vector *)c;
  if (vector_size((Vector *)v) >= v->capacity) {
    size_t new_size =
        checked_product(v->capacity * sizeof(void *), 2, SIZE_MAX);
    vector_resize(v, new_size);
    v->capacity = new_size / sizeof(void *);
  }
  size_t size = v->size;
  v->size++;
  vector_set((Vector *)v, size, x);
}

static void *vector_delete(Container *c, const void *x) {
  inline void shift_right(void * *a, size_t length, size_t offset, size_t x) {
    size_t i;
    for (i = offset; i < (length - x); i++)
      a[i] = a[i + x];
  }
  inline size_t vector_indexof(Vector * v, const void * x) {
    size_t i;
    size_t size = vector_size(v);
    for (i = 0; i < size; i++)
      if (vector_get(v, i) == x)
        return i;
  }
  inline size_t max(size_t a, size_t b) { return a > b ? a : b; }

  Vector *v = (Vector *)c;
  _Vector *_v = (_Vector *)v;
  size_t size = vector_size(v);
  size_t _capacity = max(_v->capacity * 0.33, DEFAULT_CAPACITY);
  if (size < _capacity) {
    vector_resize(_v, _capacity * sizeof(void *));
    _v->capacity = _capacity;
  }
  void **array = _v->array;
  size_t i = vector_indexof(v, x);
  void *o = array[i];
  shift_right(array, size, i, 1);
  _v->size--;
  return o;
}

static void vector_free(Object *o) {
  free(((_Vector *)o)->array);
  free(o);
}

Vector *vector_new() {
  static vector_vtable vtable = {
    { { { .class = "vector",
          .free = vector_free,
          .to_string = _object_to_string },
        .iterator = _vector_iterator },
      .search = _vector_search, .empty = _vector_empty,
      .insert = _vector_insert, .delete = vector_delete },
    .set = _vector_set, .get = _vector_get, .size = _vector_size
  };

  _Vector *v = malloc(sizeof(_Vector));
  v->vtable = &vtable;
  v->capacity = DEFAULT_CAPACITY;
  v->array = malloc(sizeof(void *) * v->capacity);
  v->size = 0;
  return (Vector *)v;
}

size_t vector_size(const Vector *v) {
  return v->vtable->size(contract_requires_non_null(v));
}

void vector_set(Vector *v, size_t i, void *x) {
  contract_requires(i < vector_size(contract_requires_non_null(v)));
  v->vtable->set(v, i, x);
}

void *vector_get(const Vector *v, size_t i) {
  contract_requires(i < vector_size(contract_requires_non_null(v)));
  return v->vtable->get(v, i);
}

void *_vector_search(const Container *c, const void *x) {
  const Vector *v = (const Vector *)c;
  size_t i;
  size_t size = vector_size(v);
  for (i = 0; i < size; i++) {
    void *_x = vector_get(v, i);
    if (_x == x)
      return _x;
  }
  return NULL;
}

bool _vector_empty(const Container *c) { return vector_size((Vector *)c) == 0; }
