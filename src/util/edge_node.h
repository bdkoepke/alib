#ifndef EDGE_NODE_H
#define EDGE_NODE_H

#include "../lang/compare.h"
#include "container.h"

typedef struct _edge_node_vtable edge_node_vtable;
typedef struct {
  edge_node_vtable *vtable;
} EdgeNode;
struct _edge_node_vtable {
  container_vtable container;
  void *(*get)(const EdgeNode *);
  void (*set)(EdgeNode *, void *);
};

EdgeNode *edge_node_new(void *x);
void *edge_node_get(const EdgeNode *e);
void edge_node_set(EdgeNode *e, void *x);

#endif /* EDGE_NODE_H */
