#include "mutable_container.h"
#include "../diag/contract.h"

#include <stdlib.h>

void mutable_container_insert(MutableContainer *m, void *x) {
  contract_requires(m != NULL);
  m->vtable->insert(m, x);
  contract_ensures(container_search((Container *)m, x) == x);
}

void mutable_container_delete(MutableContainer *m, const void *x) {
	Container *c = (Container *)m;
  contract_requires(m != NULL && !container_empty(c));
  contract_weak_requires(container_search(c, x) == x);
  m->vtable->delete (m, x);
  contract_ensures(container_search(c, x) == NULL);
}
