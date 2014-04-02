#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "mutable_container.h"

#include <stddef.h>

typedef struct _array_list_vtable array_list_vtable;
typedef struct ArrayList {
  array_list_vtable *vtable;
} ArrayList;
struct _array_list_vtable {
  mutable_container_vtable container;
  void (*set)(ArrayList *, size_t, void *);
  void *(*get)(const ArrayList *, size_t);
  size_t (*size)(const ArrayList *);
};

/**
 * Creates a new default array list.
 *
 * @return a new empty array list.
 */
ArrayList *array_list_new();

/**
 * Gets the number of objects in the  specified array list.
 *
 * @param a the array list to get the size of.
 * @return the number of objects in the array.
 */
size_t array_list_size(const ArrayList *a);

/**
 * Sets the specified index to the specified object in the array.
 *
 * @param a the array list to set the object in.
 * @param i the index to place the object in.
 * @param x the object to insert.
 */
void array_list_set(ArrayList *a, size_t i, void *x);

/**
 * Gets the object at the specified index in the array.
 *
 * @param a the array list to get the object from.
 * @param i the index of the object to get.
 * @return the object.
 */
void *array_list_get(const ArrayList *a, size_t i);

void *_array_list_search(const Container *, const void *);
bool _array_list_empty(const Container *);

#endif /* ARRAY_LIST_H */
