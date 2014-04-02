#ifndef MUTABLE_CONTAINER_H
#define MUTABLE_CONTAINER_H

#include "../lang/object.h"
#include "container.h"

#include <stdbool.h>

typedef struct _mutable_container_vtable mutable_container_vtable;
typedef struct MutableContainer {
  mutable_container_vtable *vtable;
} MutableContainer;
struct _mutable_container_vtable {
	container_vtable container;
  void (*insert)(MutableContainer *, void *);
  void (*delete)(MutableContainer *, const void *);
};

/**
 * Inserts the specified object into the container.
 *
 * @param c the container to insert the object into.
 * @param x the object to insert into the container.
 */
void mutable_container_insert(MutableContainer *m, void *x);

/**
 * Deletes the specified object from the container.
 *
 * @param c the container to delete the object from.
 * @param x the object to delete from the container.
 */
void mutable_container_delete(MutableContainer *m, const void *x);

#endif /* MUTABLE_CONTAINER_H */
