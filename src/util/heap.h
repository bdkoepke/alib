#ifndef HEAP_H
#define HEAP_H

#include "../lang/object.h"
#include "compare.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _heap_vtable heap_vtable;
typedef struct Heap {
  heap_vtable *vtable;
} Heap;
struct _heap_vtable {
  object_vtable object;
  void (*insert)(Heap *, void *);
  void *(*extract_min)(Heap *);
  size_t (*size)(const Heap *);
  bool (*compare)(const Heap *, const void *, size_t);
};

Heap *heap_new(Compare);
Heap *heap_new_from_array(Compare, void *, size_t);

void heap_insert(Heap *, void *);
void *heap_extract_min(Heap *);
bool heap_compare(const Heap *, const void *, size_t);
size_t heap_size(const Heap *);

bool heap_empty(const Heap *);

#endif /* HEAP_H */
