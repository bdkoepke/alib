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

GraphIterator *graph_breadth_first(const Graph *g, const void *s) {
  return contract_ensures_non_null(
      g->vtable->breadth_first(contract_requires_non_null(g), s));
}

GraphIterator *graph_depth_first(const Graph *g, const void *s) {
  return contract_ensures_non_null(
      g->vtable->depth_first(contract_requires_non_null(g), s));
}

typedef enum {
  Undiscovered,
  Discovered,
  Processed
} VertexState;

typedef struct {
  graph_iterator_vtable *vtable;
  const Graph *g;
  Queue *q;
  VertexState *s;
  size_t length;
} BreadthFirstGraphIterator;

static void breadth_first_graph_iterator_free(Object *o) {
  object_free((Object *)((BreadthFirstGraphIterator *)o)->q);
  free(o);
}

GraphIterator *_directed_graph_breadth_first(const DirectedGraph *g,
                                             const void *s) {}

GraphIterator *_undirected_graph_breadth_first(const UndirectedGraph *g,
                                               const void *s) {
  static graph_iterator_vtable vtable = {
    {.class = "breadth_first_graph_iterator",
         .free = breadth_first_graph_iterator_free, .to_string =
                                                        _object_to_string },
  };
  BreadthFirstGraphIterator *b = malloc(sizeof(BreadthFirstGraphIterator));
  b->vtable = &vtable;
  b->g = g;
  b->q = linked_queue_new();
  //b->length = set_size(graph_vertices(g));
  b->s = malloc(sizeof(VertexState) * b->length);
  return (GraphIterator *)b;
}

GraphIterator *_directed_graph_depth_first(const DirectedGraph *g,
                                           const void *s) {}

GraphIterator *_undirected_graph_depth_first(const UndirectedGraph *g,
                                             const void *s) {}
