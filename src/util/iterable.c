#include "../diag/contract.h"
#include "iterable.h"

Iterator *iterable_iterator(const Iterable *i) {
  return contract_ensures_non_null(
      i->vtable->iterator(contract_requires_non_null(i)));
}

void iterable_foreach(const Iterable *i, apply a, void *user_data) {
  Iterator *_i = iterable_iterator(contract_requires_non_null(i));
  iterator_foreach(_i, contract_requires_non_null(a), user_data);
  object_free((Object *)_i);
}
