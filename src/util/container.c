#include "../diag/contract.h"
#include "container.h"

#include <stdlib.h>

void *container_search(const Container *c, const void *x) {
  return c->vtable->search(contract_requires_non_null(c), x);
}

bool container_empty(const Container *c) {
  return c->vtable->empty(contract_requires_non_null(c));
}

void container_insert(Container *c, void *x) {
  c->vtable->insert(contract_requires_non_null(c), x);
  contract_weak_ensures_equal(container_search(c, x), x);
}

void *container_delete(Container *c, const void *x) {
  contract_weak_requires_equal(container_search(c, x), x);
  void *o = contract_ensures_equal(
      c->vtable->delete (contract_requires_non_null(c), x), x);
  contract_weak_ensures_equal(container_search(c, x), NULL);
  return o;
}
