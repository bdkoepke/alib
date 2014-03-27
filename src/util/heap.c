#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "heap.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  heap_vtable *vtable;
  size_t size;
  size_t capacity;
  Compare c;
  void **p;
} _Heap;

static inline size_t heap_left_child(size_t n) {
  contract_requires(n < SIZE_MAX / 2 - 1);
  return n * 2;
}

static inline size_t heap_right_child(size_t n) {
  contract_requires(n < SIZE_MAX / 2);
  return n * 2 + 1;
}

static inline void swap(void **p, size_t n, size_t parent) {
  void *t = p[n];
  p[n] = p[parent], p[parent] = t;
}

static inline void heap_bubble_down(_Heap *h, size_t n) {
  inline size_t heap_min(_Heap * h, size_t a, size_t b) {
    inline void *heap_get(_Heap * h, size_t n) {
      return n < h->size ? h->p[n] : NULL;
    }

    void *left = heap_get(h, a);
    void *right = heap_get(h, b);
    if (left == NULL)
      return b;
    if (right == NULL)
      return a;
    return h->c(left, right) < 0 ? a : b;
  }

  if (n >= h->size)
    return;
  size_t min_index =
      heap_min(h, n, heap_min(h, heap_left_child(n), heap_right_child(n)));
  if (min_index != n) {
    swap(h->p, n, min_index);
    heap_bubble_down(h, min_index);
  }
}

static size_t _heap_size(const Heap *h) { return ((_Heap *)h)->size; }

static void _heap_insert(Heap *_h, void *x) {
  inline void heap_bubble_up(_Heap * h, size_t n) {
    inline size_t heap_parent(size_t n) {
      contract_requires(n != 0);
      return n / 2;
    }
    if (n == 0)
      return;
    size_t parent = heap_parent(n);
    if (h->c(h->p[parent], h->p[n]) > 0) {
      swap(h->p, n, parent);
      heap_bubble_up(h, parent);
    }
  }

  _Heap *h = (_Heap *)_h;
  if (h->size >= h->capacity) {
    size_t capacity =
        checked_product(h->capacity, 2 * sizeof(void *), SIZE_MAX);
    h->p = realloc(h->p, capacity);
    h->capacity = capacity / sizeof(void *);
  }

  h->p[h->size] = x;
  heap_bubble_up(h, h->size);
  h->size++;
}

static void *_heap_extract_min(Heap *_h) {
  _Heap *h = (_Heap *)_h;
  void *min = h->p[0];
  h->size--;
  h->p[0] = h->p[h->size];
  heap_bubble_down(h, 0);
  return min;
}

static bool _heap_empty(const Heap *h) { return ((const _Heap *)h)->size == 0; }

static bool _heap_compare(const Heap *h, const void *x, size_t k) {
  bool __heap_compare(const _Heap * h, const void * x, size_t n, size_t k) {
    if (k <= 0 || n >= h->size || h->c(h->p[n], x) >= 0)
      return k;
    return __heap_compare(h, x, heap_right_child(n),
                          __heap_compare(h, x, heap_left_child(n), k - 1));
  }
  return __heap_compare((_Heap *)h, x, 0, k);
}

static void heap_free(Object *o) {
  _Heap *h = (_Heap *)o;
  free(h->p);
  free(h);
}

static Heap *_heap_new(Compare c, void **p, size_t size, size_t capacity) {
  static heap_vtable vtable = {
    {.free = heap_free }, .insert = _heap_insert,
                              .extract_min = _heap_extract_min,
                              .size = _heap_size, .compare = _heap_compare
  };

  contract_requires(c != NULL && p != NULL && capacity > 0);

  _Heap *h = malloc(sizeof(_Heap));
  h->vtable = &vtable;
  h->size = size;
  h->capacity = capacity;
  h->c = c;
  h->p = p;
  return (Heap *)h;
}

Heap *heap_new(Compare c) {
  static const size_t DEFAULT_CAPACITY = 11;
  return _heap_new(c, calloc(DEFAULT_CAPACITY, sizeof(void *)), 0,
                   DEFAULT_CAPACITY);
}

Heap *heap_new_from_array(Compare c, void *a, size_t length) {
  Heap *h = _heap_new(c, a, length, length);
  size_t i;
  for (i = 0; i < length; i++)
    heap_bubble_down((_Heap *)h, (length - 1) - i);
  return h;
}

void heap_insert(Heap *h, void *x) {
  contract_requires(h != NULL && x != NULL);
  h->vtable->insert(h, x);
}

void *heap_extract_min(Heap *h) {
  contract_requires(h != NULL && !heap_empty(h));
  return h->vtable->extract_min(h);
}

bool heap_empty(const Heap *h) {
  contract_requires(h != NULL);
  return heap_size(h) == 0;
}

size_t heap_size(const Heap *h) {
  contract_requires(h != NULL);
  return h->vtable->size(h);
}

bool heap_compare(const Heap *h, const void *x, size_t k) {
  contract_requires(h != NULL && x != NULL && k < heap_size(h));
  return h->vtable->compare(h, x, k);
}
