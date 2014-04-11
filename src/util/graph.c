#include "../diag/contract.h"
#include "graph.h"
#include "linked_queue.h"

#include <stdlib.h>

bool graph_adjacent(const Graph *g, const void *x, const void *y) {
  return g->vtable
      ->adjacent(contract_requires_non_null(g), contract_requires_non_null(x),
                 contract_requires_non_null(y));
}

const Set *graph_neighbors(const Graph *g, const void *x) {
  return contract_ensures_non_null(g->vtable->neighbors(
      contract_requires_non_null(g), contract_requires_non_null(x)));
}

const Set *graph_vertices(const Graph *g) {
  return contract_ensures_non_null(
      g->vtable->vertices(contract_requires_non_null(g)));
}

void graph_insert_edge(Graph *g, void *x, void *y) {
  contract_weak_requires(!graph_adjacent(g, x, y));
  g->vtable->insert_edge(contract_requires_non_null(g),
                         contract_requires_non_null(x),
                         contract_requires_non_null(y));
  contract_weak_ensures(graph_adjacent(g, x, y));
}

void graph_delete_edge(Graph *g, const void *x, const void *y) {
  contract_weak_requires(graph_adjacent(g, x, y));
  g->vtable->delete_edge(contract_requires_non_null(g),
                         contract_requires_non_null(x),
                         contract_requires_non_null(y));
  contract_weak_requires(!graph_adjacent(g, x, y));
}

GraphIterator *graph_breadth_first(const Graph *g) {
  return contract_ensures_non_null(
      g->vtable->breadth_first(contract_requires_non_null(g)));
}

GraphIterator *graph_depth_first(const Graph *g) {
  return contract_ensures_non_null(
      g->vtable->depth_first(contract_requires_non_null(g)));
}

GraphIterator *_directed_graph_breadth_first(const DirectedGraph *g) {}

GraphIterator *_undirected_graph_breadth_first(const UndirectedGraph *g) {}

GraphIterator *_directed_graph_depth_first(const DirectedGraph *g) {}

GraphIterator *_undirected_graph_depth_first(const UndirectedGraph *g) {}
