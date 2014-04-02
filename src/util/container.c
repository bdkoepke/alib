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
