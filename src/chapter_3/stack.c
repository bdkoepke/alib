#include "../contract.h"
#include "node.h"
#include "stack.h"

#include <stdlib.h>

typedef struct {
  stack_vtable *vtable;
  Node *head;
} _Stack;

static void _stack_push(Stack *s, void *x) {
  ((_Stack *)s)->head =
      stack_empty(s) ? node_new_leaf(x) : node_new(x, ((_Stack *)s)->head);
}

static void *_stack_pop(Stack *_s) {
  _Stack *s = (_Stack *)_s;
  Node *head = s->head;
  s->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

static bool _stack_empty(const Stack *s) { return ((_Stack *)s)->head == NULL; }

Stack *stack_new() {
  static stack_vtable vtable = {
    {.free = _stack_free }, .push = _stack_push, .pop = _stack_pop,
                                                     .empty = _stack_empty
  };

  _Stack *s = malloc(sizeof(_Stack));
  s->head = NULL;
  s->vtable = &vtable;
  return (Stack *)s;
}

void stack_push(Stack *s, void *x) {
  contract_requires(s != NULL);
  s->vtable->push(s, x);
  contract_ensures(!stack_empty(s));
}

void *stack_pop(Stack *s) {
  contract_requires(s != NULL && !stack_empty(s));
  return s->vtable->pop(s);
}

bool stack_empty(const Stack *s) {
  contract_requires(s != NULL);
  return s->vtable->empty(s);
}

void _stack_free(Object *o) {
  Stack *s = (Stack *)o;
  while (!stack_empty(s))
    stack_pop(s);
  free(s);
}
