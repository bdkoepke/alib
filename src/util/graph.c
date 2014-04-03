#include "../diag/contract.h"
#include "graph.h"

#include <stdlib.h>

bool graph_adjacent(const Graph *g, const void *x, const void *y) {
  contract_requires(g != NULL && x != NULL && y != NULL);
  return g->vtable->adjacent(g, x, y);
}

const Container *graph_neighbors(const Graph *g, const void *x) {
  contract_requires(g != NULL && x != NULL);
  return g->vtable->neighbors(g, x);
}

void graph_insert_edge(Graph *g, void *x, void *y) {
  contract_requires(g != NULL && x != NULL && y != NULL);
  g->vtable->insert_edge(g, x, y);
  contract_weak_requires(graph_adjacent(g, x, y));
}

void graph_delete_edge(Graph *g, const void *x, const void *y) {
  contract_requires(g != NULL && x != NULL && y != NULL);
  contract_weak_requires(graph_adjacent(g, x, y));
  g->vtable->delete_edge(g, x, y);
  contract_weak_requires(!graph_adjacent(g, x, y));
}

/* void *graph_node_value(const Graph *g, const void *x) {
  contract_requires(g != NULL && x != NULL);
  return g->vtable->node_value(g, x);
}

void graph_set_node_value(Graph *g, void *x, void *a) {
  contract_requires(g != NULL && x != NULL);
  g->vtable->set_node_value(g, x, a);
}

void *graph_edge_value(const Graph *g, const void *x, const void *y) {
  contract_requires(g != NULL && x != NULL && y != NULL);
  return g->vtable->edge_value(g, x, y);
}

void graph_set_edge_value(Graph *g, void *x, void *y, void *a) {
  contract_requires(g != NULL && x != NULL && y != NULL);
  g->vtable->set_edge_value(g, x, y, a);
} */
