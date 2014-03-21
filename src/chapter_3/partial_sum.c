#include "../contract.h"
#include "partial_sum.h"

#include <stdlib.h>

typedef struct {
  partial_sum_vtable *vtable;
  Compare c;
} _PartialSum;

void _partial_sum_add(PartialSum *p, void *k, void *y) {}

void *_partial_sum_values(const PartialSum *p, const void *y) { return NULL; }

void _partial_sum_insert(PartialSum *p, void *k, void *y) {}

void _partial_sum_delete(PartialSum *p, void *k) {}

void partial_sum_free(Object *o) {}

PartialSum *partial_sum_new(Compare c) {
  static partial_sum_vtable vtable = {
    {.free = partial_sum_free },
        .add = _partial_sum_add, .values = _partial_sum_values,
        .insert = _partial_sum_insert, .delete = _partial_sum_delete
  };
  _PartialSum *p = malloc(sizeof(PartialSum));
  p->vtable = &vtable;
  p->c = c;
  return (PartialSum *)p;
}

void partial_sum_add(PartialSum *p, void *k, void *y) {
  contract_requires(p != NULL && k != NULL);
  p->vtable->add(p, k, y);
}

void *partial_sum_values(const PartialSum *p, const void *y) {
  contract_requires(p != NULL && y != NULL);
  return p->vtable->values(p, y);
}

void partial_sum_insert(PartialSum *p, void *k, void *y) {
  contract_requires(p != NULL && k != NULL);
  p->vtable->insert(p, k, y);
}

void partial_sum_delete(PartialSum *p, void *k) {
  contract_requires(p != NULL && k != NULL);
  p->vtable->delete (p, k);
}
