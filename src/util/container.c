#include "container.h"
#include "../diag/contract.h"

#include <stdlib.h>

void *container_search(const Container *c, const void *x) {
  contract_requires(c != NULL);
  return c->vtable->search(c, x);
}

bool container_empty(const Container *c) {
  contract_requires(c != NULL);
  return c->vtable->empty(c);
}

void container_insert(Container *c, void *x) {
  contract_requires(c != NULL);
  c->vtable->insert(c, x);
  contract_weak_requires(container_search(c, x) == x);
}

void *container_delete(Container *c, const void *x) {
  contract_requires(c != NULL);
  contract_weak_requires(container_search(c, x) == x);
  void *o = c->vtable->delete (c, x);
  contract_weak_requires(container_search(c, x) == NULL);
	return o;
}
