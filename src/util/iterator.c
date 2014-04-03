#include "../diag/contract.h"
#include "iterator.h"

#include <stdio.h>

void *iterator_current(const Iterator *i) {
  contract_requires(i != NULL);
  return i->vtable->current(i);
}

bool iterator_move_next(Iterator *i) {
  contract_requires(i != NULL);
  return i->vtable->move_next(i);
}

void *_iterator_current_invalid_state(const Iterator *i) {
  contract_requires(false);
  return NULL;
}

bool _iterator_move_next_invalid_state(Iterator *i) {
  contract_requires(false);
  return false;
}

iterator_vtable iterator_vtable_invalid_state = {
  {.free = _object_free }, .current = _iterator_current_invalid_state,
                               .move_next = _iterator_move_next_invalid_state
};
