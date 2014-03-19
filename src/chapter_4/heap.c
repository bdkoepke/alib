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

Heap *heap_new() {
	_Heap *h = malloc(sizeof(_Heap));
	h->size = 0;
	h->capacity = DEFAULT_CAPACITY;
	h->p = calloc(h->capacity, sizeof(void *));
	return (Heap *)h;
}
