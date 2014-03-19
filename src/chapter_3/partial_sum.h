#ifndef PARTIAL_SUM_H
#define PARTIAL_SUM_H

#include "compare.h"
#include "../object.h"

typedef struct _partial_sum_vtable partial_sum_vtable;
typedef struct PartialSum {
  partial_sum_vtable *vtable;
} PartialSum;
struct _partial_sum_vtable {
  object_vtable vtable;
  void (*add)(PartialSum *, void *, void *);
  void (*insert)(PartialSum *, void *, void *);
  void (*delete)(PartialSum *, void *);
  void *(*values)(const PartialSum *, const void *);
};

PartialSum *partial_sum_new(Compare);

void partial_sum_add(PartialSum *, void *, void *);
void *partial_sum_values(const PartialSum *, const void *);
void partial_sum_insert(PartialSum *, void *, void *);
void partial_sum_delete(PartialSum *, void *);

#endif /* PARTIAL_SUM_H */
