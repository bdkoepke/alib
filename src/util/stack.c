#include "../diag/contract.h"
#include "stack.h"

#include <stdlib.h>

void stack_push(Stack *s, void *x) {
  contract_requires(s != NULL);
  s->vtable->push(s, x);
  contract_ensures(!container_empty((Container *)s));
}

void *stack_pop(Stack *s) {
  contract_requires(s != NULL && !container_empty((Container *)s));
  return s->vtable->pop(s);
}

const void *stack_peek(const Stack *s) {
  contract_requires(s != NULL && !container_empty((Container *)s));
  return s->vtable->peek(s);
}

void _stack_insert(MutableContainer *c, void *x) { stack_push((Stack *)c, x); }

void _stack_free(Object *o) {
  Stack *s = (Stack *)o;
  while (!container_empty((Container *)s))
    stack_pop(s);
  free(s);
}
