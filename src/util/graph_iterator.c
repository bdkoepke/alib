#include "../diag/contract.h"
#include "graph_iterator.h"

#include <stdlib.h>

EdgeNode *graph_iterator_current_edge(const GraphIterator *g) {
  return contract_ensures_non_null(
      g->vtable->current_edge(contract_requires_non_null(g)));
}

void *graph_iterator_current_vertex(const GraphIterator *g) {
  return contract_ensures_non_null(
      g->vtable->current_vertex(contract_requires_non_null(g)));
}

bool graph_iterator_move_next_vertex(GraphIterator *g) {
  return g->vtable->move_next_vertex(contract_requires_non_null(g));
}

bool graph_iterator_move_next_edge(GraphIterator *g) {
  return g->vtable->move_next_edge(contract_requires_non_null(g));
}

EdgeNode *_graph_iterator_current_edge_invalid_state(const GraphIterator *g) {
  contract_fail();
  return NULL;
}

void *_graph_iterator_current_vertex_invalid_state(const GraphIterator *g) {
  contract_fail();
  return NULL;
}

bool _graph_iterator_move_next_vertex_invalid_state(GraphIterator *g) {
  contract_fail();
  return false;
}

bool _graph_iterator_move_next_edge_invalid_state(GraphIterator *g) {
  contract_fail();
  return false;
}
