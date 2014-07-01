#include "../diag/contract.h"
#include "graph_visitor.h"

void graph_visitor_vertex_early(GraphVisitor *g, const void *v) {
  return g->vtable->vertex_early(contract_requires_non_null(g),
                                 contract_requires_non_null(v));
}

void graph_visitor_edge(GraphVisitor *g, const void *x, const void *y) {
  return g->vtable->edge(contract_requires_non_null(g),
                         contract_requires_non_null(x),
                         contract_requires_non_null(y));
}

void graph_visitor_vertex_late(GraphVisitor *g, const void *v) {
  return g->vtable->vertex_late(contract_requires_non_null(g),
                                contract_requires_non_null(v));
}
