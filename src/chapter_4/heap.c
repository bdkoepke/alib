#include "contract.h"
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

static const size_t DEFAULT_CAPACITY = 11;

static inline size_t heap_parent(size_t n) {
	return n / 2;
}

static inline size_t heap_left_child(size_t n) {
	contract_requires(n < ((SIZE_MAX / 2) - 1));
	return n * 2;
}

static inline size_t heap_right_child(size_t n) {
	contract_requires(n < (SIZE_MAX / 2));
	return (n * 2) + 1;
}

static inline size_t checked_product(size_t multiplicand, size_t multiplier,
                                     size_t _default) {
  size_t product = multiplicand * multiplier;
  return product < multiplicand ? _default : product;
}

static inline void swap(void **p, size_t n, size_t parent) {
	void *t = p[n];
	p[n] = p[parent];
	p[parent] = t;
}

static inline void heap_bubble_up(void **p, size_t n, Compare c) {
	if (n == 0)
		return;

	size_t parent = heap_parent(n);
	if (c(p[parent], p[n]) < 0) {
		swap(p, n, parent);
		heap_bubble_up(p, parent, c);
	}
}

static inline void heap_bubble_down(void **p, size_t n, Compare c) {
	size_t left = heap_left_child(n);
	size_t right = heap_right_child(n);
}

static void _heap_insert(Heap *_h, void *x) {
	_Heap *h = (_Heap *)_h;
	if (h->size >= h->capacity) {
		size_t capacity = checked_product(h->capacity, 2 * sizeof(void *), SIZE_MAX);
		h->p = realloc(h->p, capacity);
		h->capacity = capacity / sizeof(void *);
	}

	h->p[h->size] = x;
	heap_bubble_up(h->p, h->size, h->c);
	h->size++;
}

static void *_heap_extract_min(Heap *_h) {
	_Heap *h = (_Heap *)_h;
	void *min = h->p[0];
	h->size--;
	h->p[0] = h->p[h->size];
	heap_bubble_down(h->p, 0, h->c);
	return min;
}

static bool _heap_empty(const Heap *h) {
	return ((const _Heap *)h)->size == 0;
}

static void heap_free(Object *o) {
  _Heap *h = (_Heap *)o;
	free(h->p);
	free(h);
}

Heap *heap_new(Compare c) {
  static heap_vtable vtable = {
    {.free = heap_free }, .insert = _heap_insert,
                               .extract_min = _heap_extract_min, .empty =
                                                                     _heap_empty
  };
	
	contract_requires(c != NULL);

  _Heap *h = malloc(sizeof(_Heap));
  h->vtable = &vtable;
  h->size = 0;
  h->capacity = DEFAULT_CAPACITY;
	h->c = c;
  h->p = calloc(h->capacity, sizeof(void *));
  return (Heap *)h;
}

void heap_insert(Heap *h, void *x) {
  contract_requires(h != NULL && x != NULL);
  return h->vtable->insert(h, x);
}

void *heap_extract_min(Heap *h) {
  contract_requires(h != NULL && ! heap_empty(h));
  return h->vtable->extract_min(h);
}

bool heap_empty(const Heap *h) {
  contract_requires(h != NULL);
  return h->vtable->empty(h);
}
