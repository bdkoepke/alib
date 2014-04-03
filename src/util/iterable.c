#include "../diag/contract.h"
#include "iterable.h"

#include <stdio.h>

Iterator *iterable_iterator(const Iterable *i) {
  contract_requires(i != NULL);
  return i->vtable->iterator(i);
}
