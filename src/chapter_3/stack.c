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
      container_empty((Container *)s) ? node_new_leaf(x)
                                      : node_new(x, ((_Stack *)s)->head);
}

static void *_stack_pop(Stack *_s) {
  _Stack *s = (_Stack *)_s;
  Node *head = s->head;
  s->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

static const void *_stack_peek(const Stack *s) {
  return ((_Stack *)s)->head->x;
}

static void _stack_reverse(Stack *_s) {
  _Stack *s = (_Stack *)_s;
  if (container_empty((Container *)s))
    return;

  Node *node = s->head;
  Node *next = node->n;
  Node *_next;
  for (node->n = NULL; next != NULL; next = _next) {
    _next = next->n;
    next->n = node;
    node = next;
  }
  s->head = node;
}

void _stack_insert(Container *c, void *x) { stack_push((Stack *)c, x); }

static void *stack_search(const Container *c, const void *x) {
  const _Stack *s = (const _Stack *)c;
  Node *node;
  for (node = s->head; node != NULL; node = node->n)
    if (node->x == x)
      return node->x;
  return NULL;
}

static void stack_delete(Container *c, const void *x) {
  _Stack *s = (_Stack *)c;
  if (s->head->x != x) {
    Node *node;
    Node *next = s->head->n;
    for (node = s->head; next != NULL; node = next) {
      next = node->n;
      if (next->x == x) {
        node->n = next->n;
        break;
      }
    }
  } else {
    Node *head = s->head;
    s->head = head->n;
    free(head);
  }
}

static bool stack_empty(const Container *c) {
  return ((_Stack *)c)->head == NULL;
}

Stack *stack_new() {
  static stack_vtable vtable = {
    { {.free = _stack_free },
          .insert = _stack_insert, .search = stack_search,
          .delete = stack_delete, .empty = stack_empty },
        .push = _stack_push, .pop = _stack_pop, .peek = _stack_peek,
        .reverse = _stack_reverse
  };

  _Stack *s = malloc(sizeof(_Stack));
  s->head = NULL;
  s->vtable = &vtable;
  return (Stack *)s;
}

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

void stack_reverse(Stack *s) {
  contract_requires(s != NULL);
  return s->vtable->reverse(s);
}

void _stack_free(Object *o) {
  Stack *s = (Stack *)o;
  while (!container_empty((Container *)s))
    stack_pop(s);
  free(s);
}
