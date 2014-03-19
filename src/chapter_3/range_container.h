#ifndef RANGE_CONTAINER_H
#define RANGE_CONTAINER_H

#include "../object.h"

#include <stddef.h>

typedef struct _range_container_vtable range_container_vtable;
typedef struct RangeContainer {
  range_container_vtable *vtable;
} RangeContainer;
struct _range_container_vtable {
  object_vtable object;
  void (*insert)(RangeContainer *, void *);
  void *(*query)(const RangeContainer *, size_t i, size_t j);
};

RangeContainer *array_range_container_new();

void range_container_insert(RangeContainer *, void *);
void *range_container_query(const RangeContainer *, size_t i, size_t j);

#endif /* RANGE_CONTAINER_H */
