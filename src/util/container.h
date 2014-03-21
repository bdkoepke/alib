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
  void (*delete)(Container *, const void *);
  bool (*empty)(const Container *);
};

void *container_search(const Container *, const void *);
void container_insert(Container *, void *);
void container_delete(Container *, const void *);
bool container_empty(const Container *);

#endif /* CONTAINER_H */
