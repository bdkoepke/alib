#ifndef SORTED_SET_H
#define SORTED_SET_H

#include "compare.h"
#include "../object.h"

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
  void *(*delete)(SortedSet *, size_t);
  size_t (*size)(const SortedSet *);
};

SortedSet *sorted_set_new(Compare);

bool sorted_set_member(const SortedSet *, const void *);
void sorted_set_insert(SortedSet *, void *);
void *sorted_set_delete(SortedSet *, size_t);
bool sorted_set_empty(const SortedSet *);
size_t sorted_set_size(const SortedSet *);

#endif /* SORTED_SET_H */
