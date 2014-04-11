#include "../diag/contract.h"
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
    {.class = "partial_sum", .free = partial_sum_free, .to_string =
                                                           _object_to_string },
        .add = _partial_sum_add, .values = _partial_sum_values,
        .insert = _partial_sum_insert, .delete = _partial_sum_delete
  };
  _PartialSum *p = malloc(sizeof(PartialSum));
  p->vtable = &vtable;
  p->c = c;
  return (PartialSum *)p;
}

void partial_sum_add(PartialSum *p, void *k, void *y) {
  p->vtable->add(contract_requires_non_null(p), contract_requires_non_null(k),
                 contract_requires_non_null(y));
}

void *partial_sum_values(const PartialSum *p, const void *y) {
  return p->vtable
      ->values(contract_requires_non_null(p), contract_requires_non_null(y));
}

void partial_sum_insert(PartialSum *p, void *k, void *y) {
  p->vtable
      ->insert(contract_requires_non_null(p), contract_requires_non_null(k), y);
}

void partial_sum_delete(PartialSum *p, void *k) {
  p->vtable
      ->delete (contract_requires_non_null(p), contract_requires_non_null(k));
}
