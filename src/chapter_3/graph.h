#ifndef GRAPH_H
#define GRAPH_H

#include "iterable.h"

typedef struct _graph_vtable graph_vtable;
typedef struct {
  graph_vtable *vtable;
} Graph;
struct _graph_vtable {
  void (*insert)(Graph *, const void *, void *);
  void *(*bfs)(Graph *, const void *);
  void *(*dfs)(Graph *, const void *);
  Iterable *(*find_path)(Graph *, const void *, const void *);
  void (*free)(Graph *);
};

void graph_insert(Graph *, const void *, void *);
void *graph_bfs(Graph *, const void *);
void *graph_dfs(Graph *, const void *);
Iterable *graph_find_path(Graph *, const void *, const void *);
void graph_free(Graph *);

#endif /* GRAPH_H */
