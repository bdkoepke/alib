#include "../diag/contract.h"
#include "stack.h"

#include <stdlib.h>

void stack_push(Stack *s, void *x) {
  s->vtable->push(contract_requires_non_null(s), x);
  contract_weak_ensures(!container_empty((Container *)s));
}

void *stack_pop(Stack *s) {
  contract_requires(!container_empty((Container *)s));
  return s->vtable->pop(contract_requires_non_null(s));
}

void *stack_peek(const Stack *s) {
  contract_requires(!container_empty((Container *)s));
  return s->vtable->peek(contract_requires_non_null(s));
}

void _stack_insert(Container *c, void *x) { stack_push((Stack *)c, x); }

void _stack_free(Object *o) {
  Stack *s = (Stack *)o;
  while (!container_empty((Container *)s))
    stack_pop(s);
  free(s);
}
