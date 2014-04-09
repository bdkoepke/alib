#include "../diag/contract.h"
#include "iterable.h"

#include <stdio.h>

Iterator *iterable_iterator(const Iterable *i) {
  return i->vtable->iterator(contract_requires_non_null(i));
}
