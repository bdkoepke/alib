#ifndef VECTOR_H
#define VECTOR_H

#include "container.h"

#include <stddef.h>

typedef struct _vector_vtable vector_vtable;
typedef struct Vector {
  vector_vtable *vtable;
} Vector;
struct _vector_vtable {
  container_vtable container;
  void (*set)(Vector *, size_t, void *);
  void *(*get)(const Vector *, size_t);
  size_t (*size)(const Vector *);
};

/**
 * Creates a new default vector.
 *
 * @return a new empty vector.
 */
Vector *vector_new();

/**
 * Gets the number of objects in the specified vector.
 *
 * @param v the vector to get the size of.
 * @return the number of objects in the array.
 */
size_t vector_size(const Vector *v);

/**
 * Sets the specified index to the specified object in the vector.
 *
 * @param v the vector to set the element in.
 * @param i the index to place the object in.
 * @param x the object to insert.
 */
void vector_set(Vector *v, size_t i, void *x);

/**
 * Gets the object at the specified index in the vector.
 *
 * @param a the vector to get the object from.
 * @param i the index of the object to get.
 * @return the object.
 */
void *vector_get(const Vector *v, size_t i);

void *_vector_search(const Container *, const void *);
bool _vector_empty(const Container *);
Iterator *_vector_iterator(const Iterable *);

#endif /* VECTOR_H */
