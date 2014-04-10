#include "../diag/contract.h"
#include "iterable.h"

#include <stdio.h>

Iterator *iterable_iterator(const Iterable *i) {
  return contract_ensures_non_null(
      i->vtable->iterator(contract_requires_non_null(i)));
}

void iterable_foreach(const Iterable *i, apply a, void *user_data) {
  iterator_foreach(iterable_iterator(contract_requires_non_null(i)),
                   contract_requires_non_null(a), user_data);
}
