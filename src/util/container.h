#ifndef CONTAINER_H
#define CONTAINER_H

#include "../lang/object.h"

#include <stdbool.h>

typedef struct _container_vtable container_vtable;
typedef struct Container {
  container_vtable *vtable;
} Container;
struct _container_vtable {
  object_vtable object;
  void *(*search)(const Container *, const void *);
  void (*insert)(Container *, void *);
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

#endif /* CONTAINER_H */
