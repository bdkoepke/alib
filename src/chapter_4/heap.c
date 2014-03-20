#include "contract.h"
#include "heap.h"

#include <stdlib.h>

typedef struct {
  heap_vtable *vtable;
  size_t size;
  size_t capacity;
  void **p;
} _Heap;

static const size_t DEFAULT_CAPACITY = 11;

static inline void *heap_parent(const Heap *h, size_t n) {
  contract_requires(n != 0);
  return ((_Heap *)h)->p[n / 2];
}

static inline void *heap_left_child(const Heap *h, size_t n) {
  contract_requires((n * 2) < ((_Heap *)h)->size);
  return ((_Heap *)h)->p[n * 2];
}

static inline void *heap_right_child(const Heap *h, size_t n) {
  contract_requires((n * 2 + 1) < ((_Heap *)h)->size);
  return ((_Heap *)h)->p[n * 2 + 1];
}

static void _heap_insert(Heap *h, void *x) {}

static void *_heap_extract_min(Heap *h) {}

static bool _heap_empty(const Heap *h) {}

Heap *heap_new() {
  static heap_vtable vtable = {
    {.free = _heap_free }, .insert = _heap_insert,
                               .extract_min = _heap_extract_min, .empty =
                                                                     _heap_empty
  };
  _Heap *h = malloc(sizeof(_Heap));
  h->vtable = &vtable;
  h->size = 0;
  h->capacity = DEFAULT_CAPACITY;
  h->p = calloc(h->capacity, sizeof(void *));
  return (Heap *)h;
}

void heap_insert(Heap *h, void *x) {
  contract_requires(h != NULL && x != NULL);
  return h->vtable->insert(h, x);
}

void *heap_extract_min(Heap *h) {
  contract_requires(h != NULL);
  return h->vtable->extract_min(h);
}

bool heap_empty(const Heap *h) {
  contract_requires(h != NULL);
  return h->vtable->empty(h);
}

void _heap_free(Object *o) {
  Heap *h = (Heap *)o;
  while (!heap_empty(h))
    heap_extract_min(h);
  free(h);
}
