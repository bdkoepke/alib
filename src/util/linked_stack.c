#include "../diag/contract.h"
#include "linked_stack.h"
#include "node.h"
#include "stack.h"

#include <stdlib.h>

struct _LinkedStack {
  stack_vtable *vtable;
  Node *head;
};

static void linked_stack_push(Stack *s, void *x) {
  node_insert(&((LinkedStack *)s)->head, x);
}

static void *linked_stack_pop(Stack *s) {
  LinkedStack *l = (LinkedStack *)s;
  Node *head = l->head;
  l->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

static const void *linked_stack_peek(const Stack *s) {
  return ((LinkedStack *)s)->head->x;
}

static void *linked_stack_search(const Container *c, const void *x) {
  return node_search(((const LinkedStack *)c)->head, x);
}

static void linked_stack_delete(Container *c, const void *x) {
  node_delete(&((LinkedStack *)c)->head, x);
}

static bool linked_stack_empty(const Container *c) {
  return node_empty(((const LinkedStack *)c)->head);
}

void linked_stack_reverse(LinkedStack *l) {
  contract_requires(l != NULL);
  if (container_empty((Container *)l))
    return;

  Node *node = l->head;
  Node *next = node->n;
  Node *_next;
  for (node->n = NULL; next != NULL; next = _next) {
    _next = next->n;
    next->n = node;
    node = next;
  }
  l->head = node;
}

size_t linked_stack_middle(const LinkedStack *l) {
  contract_requires(l != NULL && !container_empty((Container *)l));
  return node_middle(l->head);
}

LinkedStack *linked_stack_new() {
  static stack_vtable vtable = {
    { { {.free = _stack_free }, .iterator = NULL },
          .empty = linked_stack_empty, .search = linked_stack_search,
          .delete = linked_stack_delete, .insert = _stack_insert },
        .push = linked_stack_push, .pop = linked_stack_pop,
        .peek = linked_stack_peek
  };

  LinkedStack *l = malloc(sizeof(LinkedStack));
  l->head = NULL;
  l->vtable = &vtable;
  return l;
}
