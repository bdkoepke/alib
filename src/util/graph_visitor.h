#ifndef GRAPH_VISITOR_H
#define GRAPH_VISITOR_H

#include "../lang/object.h"

typedef struct _graph_visitor_vtable graph_visitor_vtable;
typedef struct {
  graph_visitor_vtable *vtable;
} GraphVisitor;
struct _graph_visitor_vtable {
  object_vtable object;
  void (*vertex_early)(GraphVisitor *, const void *);
  void (*edge)(GraphVisitor *, const void *, const void *);
  void (*vertex_late)(GraphVisitor *, const void *);
};

void graph_visitor_vertex_early(GraphVisitor *g, const void *v);
void graph_visitor_edge(GraphVisitor *g, const void *x, const void *y);
void graph_visitor_vertex_late(GraphVisitor *g, const void *v);

#endif /* GRAPH_VISITOR_H */
