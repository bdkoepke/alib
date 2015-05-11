#include "../diag/contract.h"
#include "iterator.h"

#include <stdio.h>

void *iterator_current(const Iterator *i) {
  return i->vtable->current(contract_requires_non_null(i));
}

bool iterator_move_next(Iterator *i) {
  return i->vtable->move_next(contract_requires_non_null(i));
}

void *_iterator_current_invalid_state(const Iterator *i) {
  contract_fail();
  return NULL;
}

bool _iterator_move_next_invalid_state(Iterator *i) {
  contract_fail();
  return false;
}

void iterator_foreach(Iterator *i, apply a, void *user_data) {
  contract_requires_non_null(i);
  contract_requires_non_null(a);
  while (iterator_move_next(i))
    a(user_data, iterator_current(i));
}
