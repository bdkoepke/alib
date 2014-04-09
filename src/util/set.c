#include "../diag/contract.h"
#include "set.h"

#include <stdlib.h>

const void *set_search(const Set *s, const void *x) {
  return s->vtable
      ->search(contract_requires_non_null(s), contract_requires_non_null(x));
}

bool set_empty(const Set *s) {
  return s->vtable->empty(contract_requires_non_null(s));
}

void set_insert(Set *s, void *x) {
  contract_weak_requires(set_search(s, x) == NULL);
  s->vtable
      ->insert(contract_requires_non_null(s), contract_requires_non_null(x));
  contract_weak_ensures_equal(set_search(s, x), x);
}

void *set_delete(Set *s, const void *x) {
  contract_weak_requires_equal(set_search(s, x), x);
  void *o =
      contract_ensures_equal(s->vtable->delete (contract_requires_non_null(s),
                                                contract_requires_non_null(x)),
                             x);
  contract_weak_ensures_equal(set_search(s, x), NULL);
  return o;
}
