#ifndef SORTED_SET_H
#define SORTED_SET_H

#include "object.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _sorted_set_vtable sorted_set_vtable;
typedef struct SortedSet {
  sorted_set_vtable *vtable;
} SortedSet;
struct _sorted_set_vtable {
  object_vtable object;
  bool (*member)(const SortedSet *, const void *);
  void (*insert)(SortedSet *, void *);
  void (*delete)(SortedSet *, int);
  bool (*empty)(const SortedSet *);
};

SortedSet *sorted_set_new();

bool sorted_set_member(const SortedSet *, const void *);
void sorted_set_insert(SortedSet *, void *);
void sorted_set_delete(SortedSet *, int);
bool sorted_set_empty(const SortedSet *);

#endif /* SORTED_SET_H */
