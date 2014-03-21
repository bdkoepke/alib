#ifndef ARRAY_H
#define ARRAY_H

#include "container.h"

#include <stddef.h>

typedef struct _array_vtable array_vtable;
typedef struct Array {
  array_vtable *vtable;
} Array;
struct _array_vtable {
  container_vtable container;
  void (*set)(Array *, size_t, void *);
  void *(*get)(const Array *, size_t);
  size_t (*size)(const Array *);
};

Array *array_new();

size_t array_size(const Array *);
void array_set(Array *, size_t, void *);
void *array_get(const Array *, size_t);

void *_array_search(const Container *, const void *);
bool _array_empty(const Container *);

#endif /* ARRAY_H */
