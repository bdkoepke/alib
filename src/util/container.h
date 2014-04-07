#ifndef CONTAINER_H
#define CONTAINER_H

#include "iterable.h"

#include <stdbool.h>

typedef struct _container_vtable container_vtable;
typedef struct Container {
  container_vtable *vtable;
} Container;
struct _container_vtable {
  iterable_vtable iterable;
  void *(*search)(const Container *, const void *);
  void (*insert)(Container *, void *);
  void *(*delete)(Container *, const void *);
  bool (*empty)(const Container *);
};

/**
 * Searches the specified container for the specified item.
 *
 * @param c the container to search.
 * @param x the object to search for.
 * @return the object x from the container if it exists, NULL otherwise.
 */
void *container_search(const Container *c, const void *x);

/**
 * Gets a value indicating whether the container is empty or not.
 *
 * @param c the container to check for emptiness.
 * @return true if the container is empty, false otherwise.
 */
bool container_empty(const Container *c);

/**
 * Inserts the specified object into the container.
 *
 * @param c the container to insert the object into.
 * @param x the object to insert into the container.
 */
void container_insert(Container *c, void *x);

/**
 * Deletes the specified object from the container.
 *
 * @param c the container to delete the object from.
 * @param x the object to delete from the container.
 * @return a pointer to the element that was deleted.
 */
void *container_delete(Container *c, const void *x);

#endif /* CONTAINER_H */
