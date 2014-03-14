#include "../contract.h"
#include "list.h"
#include "node.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  list_vtable *vtable;
  Node *head;
} _List;

static bool list_empty(const Container *c) {
  return ((_List *)c)->head == NULL;
}

static void list_free(Object *o) {
  const _List *l = (const _List *)o;
  Node *node;
  Node *next;
  for (node = l->head; node != NULL; node = next) {
    next = node->n;
    free(node);
  }
  free(o);
}

static void *list_search(const Container *c, const void *x) {
  const _List *l = (const _List *)c;
  Node *node;
  for (node = l->head; node != NULL; node = node->n)
    if (node->x == x)
      return node->x;
  return NULL;
}

static void list_insert(Container *c, void *x) {
  _List *l = (_List *)c;
  l->head = container_empty(c) ? node_new_leaf(x) : node_new(x, l->head);
}

static void list_delete(Container *c, const void *x) {
  _List *l = (_List *)c;

  if (l->head->x == x) {
    Node *head = l->head;
    l->head = head->n;
    free(head);
    return;
  }

  Node *node;
  Node *next = l->head->n;
  for (node = l->head; next != NULL; node = next) {
    next = node->n;
    if (next->x != x)
      continue;
    node->n = next->n;
    return;
  }
}

void *_list_car(const List *l) { return ((const _List *)l)->head->x; }

void _list_cdr(List *_l) {
  _List *l = (_List *)_l;
  Node *head = l->head;
  l->head = head->n;
  free(head);
}

void _list_reverse(List *_l) {
  _List *l = (_List *)_l;
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

List *list_new() {
  static list_vtable vtable = {
    { {.free = list_free }, .search = list_search, .insert = list_insert,
                                                       .delete = list_delete,
                                                       .empty = list_empty },
        .car = _list_car, .cdr = _list_cdr, .reverse = _list_reverse
  };

  _List *l = malloc(sizeof(_List));
  l->head = NULL;
  l->vtable = &vtable;
  return (List *)l;
}

void *list_car(const List *l) {
  contract_requires(l != NULL && !container_empty((const Container *)l));
  return l->vtable->car(l);
}

void list_cdr(List *l) {
  contract_requires(l != NULL && !container_empty((Container *)l));
  l->vtable->cdr(l);
}

void *list_cadr(List *l) {
  void *car = list_car(l);
  list_cdr(l);
  return car;
}

void list_reverse(List *l) {
  contract_requires(l != NULL);
  l->vtable->reverse(l);
}
