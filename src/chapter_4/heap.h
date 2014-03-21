#ifndef HEAP_H
#define HEAP_H

#include "../object.h"
#include "compare.h"

#include <stdbool.h>

typedef struct _heap_vtable heap_vtable;
typedef struct Heap {
  heap_vtable *vtable;
} Heap;
struct _heap_vtable {
  object_vtable object;
  void (*insert)(Heap *, void *);
  void *(*extract_min)(Heap *);
  bool (*empty)(const Heap *);
};

Heap *heap_new(Compare);

void heap_insert(Heap *, void *);
void *heap_extract_min(Heap *);
bool heap_empty(const Heap *);

#endif /* HEAP_H */
