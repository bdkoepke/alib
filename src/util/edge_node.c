#include "../diag/contract.h"
#include "edge_node.h"
#include "linked_stack.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  edge_node_vtable *vtable;
  void *x;
  LinkedStack *s;
} _EdgeNode;

static void edge_node_free(Object *o) {
	object_free((Object *)((_EdgeNode *)o)->s);
	free(o);
}

static Iterator *edge_node_iterator(const Iterable *i) {
	return iterable_iterator((const Iterable *)((_EdgeNode *)i)->s);
}

static void edge_node_insert(Container *c, void *x) {
	container_insert((Container *)((_EdgeNode *)c)->s, x);
}

static void *edge_node_search(const Container *c, const void *x) {
	return container_search((Container *)((_EdgeNode *)c)->s, x);
}

static void edge_node_delete(Container *c, const void *x) {
	container_delete((Container *)((_EdgeNode *)c)->s, x);
}

static bool edge_node_empty(const Container *c) {
	return container_empty((Container *)((_EdgeNode *)c)->s);
}

static void *_edge_node_get(const EdgeNode *e) {
	return ((const _EdgeNode *)e)->x;
}

static void _edge_node_set(EdgeNode *e, void *x) {
	((_EdgeNode *)e)->x = x;
}

EdgeNode *edge_node_new(void *x) {
  static edge_node_vtable vtable = {
    { { {.free = edge_node_free }, .iterator = edge_node_iterator },
          .insert = edge_node_insert, .search = edge_node_search,
          .empty = edge_node_empty, .delete = edge_node_delete },
        .get = _edge_node_get, .set = _edge_node_set
  };
  _EdgeNode *e = malloc(sizeof(_EdgeNode));
  e->x = x;
  e->s = linked_stack_new();
  e->vtable = &vtable;
  return (EdgeNode *)e;
}

void *edge_node_get(const EdgeNode *e) {
	contract_requires(e != NULL);
	return e->vtable->get(e);
}

void edge_node_set(EdgeNode *e, void *x) {
	contract_requires(e != NULL);
	e->vtable->set(e, x);
}
