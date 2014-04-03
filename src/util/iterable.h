#ifndef ITERABLE_H
#define ITERABLE_H

#include "iterator.h"

typedef struct _iterable_vtable iterable_vtable;
typedef struct Iterable {
  iterable_vtable *vtable;
} Iterable;
struct _iterable_vtable {
  object_vtable object;
  Iterator *(*iterator)(const Iterable *);
};

/**
 * Gets the iterator for this iterable.
 *
 * @param i the iterable to get the iterator for.
 * @return an iterator for this iterable.
 */
Iterator *iterable_iterator(const Iterable *i);

#endif /* ITERABLE_H */
