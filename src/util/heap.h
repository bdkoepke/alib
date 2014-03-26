#ifndef HEAP_H
#define HEAP_H

#include "../lang/object.h"
#include "compare.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _heap_vtable heap_vtable;
typedef struct Heap {
  heap_vtable *vtable;
} Heap;
struct _heap_vtable {
  object_vtable object;
  void (*insert)(Heap *, void *);
  void *(*extract_min)(Heap *);
  size_t (*size)(const Heap *);
  bool (*compare)(const Heap *, const void *, size_t);
};

/**
 * Creates a new min heap with the specified comparison function.
 *
 * @param c the comparison function.
 * @return a new min heap.
 */
Heap *heap_new(Compare c);

/**
 * Creates a new min heap with the specified comparison function and array.
 *
 * @param c the comparison function.
 * @param a the array to use to create the heap.
 * @param length the length of the array.
 * @return a new min heap.
 */
Heap *heap_new_from_array(Compare c, void *a, size_t length);

/**
 * Inserts the specified object into the heap.
 *
 * @param h the heap to insert the object into.
 * @param x the object to insert into the heap.
 */
void heap_insert(Heap *h, void *x);

/**
 * Extracts the next minimum object from the heap.
 *
 * @param h the heap to extract the minimum from.
 * @return the next minimum object.
 */
void *heap_extract_min(Heap *h);

/**
 * Gets a value indicating whether the object x is at least the kth
 * largest object in the heap.
 *
 * @param h the heap to get the value from.
 * @param x the object to check.
 * @param k the position that the object will be larger than if
 * 	the function is true.
 * @return true if ti is at least the kth largest object, false otherwise.
 */
bool heap_compare(const Heap *h, const void *x, size_t k);

/**
 * Gets the size of the specified heap.
 *
 * @param h the heap to get the size of.
 * @return the size of the heap.
 */
size_t heap_size(const Heap *h);

/**
 * Gets a value indicating whether the heap is empty or not.
 *
 * @param h the heap to get the emptiness of.
 * @return true if the heap is empty, false otherwise.
 */
bool heap_empty(const Heap *h);

#endif /* HEAP_H */
