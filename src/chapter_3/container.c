#include "container.h"
#include "../contract.h"

#include <stdlib.h>

void *container_search(const Container *c, const void *x) {
  contract_requires(c != NULL);
  return c->vtable->search(c, x);
}

void container_insert(Container *c, void *x) {
  contract_requires(c != NULL);
  c->vtable->insert(c, x);
  contract_ensures(container_search(c, x) == x);
}

void container_delete(Container *c, const void *x) {
  contract_requires(c != NULL && !container_empty(c) &&
                    container_search(c, x) == x);
  c->vtable->delete (c, x);
  contract_ensures(container_search(c, x) == NULL);
}

bool container_empty(const Container *c) {
  contract_requires(c != NULL);
  return c->vtable->empty(c);
}
