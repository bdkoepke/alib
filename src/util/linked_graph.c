#include "../diag/contract.h"
#include "edge_node.h"
#include "hashtable.h"
#include "linked_graph.h"
#include "linked_stack.h"

#include <stdlib.h>

typedef Set *(*set_factory)(void *user_data);

typedef struct {
  graph_vtable *vtable;
  Dictionary *d;
  size_t e, v;
  set_factory f;
  void *user_data;
} LinkedGraph;

static const Set *linked_graph_neighbors(const Graph *g, const void *x) {
  return dictionary_search(((LinkedGraph *)g)->d, x);
}

static void linked_graph_free(Object *o) {
  LinkedGraph *l = (LinkedGraph *)o;
  Graph *g = (Graph *)o;
  Iterator *i = iterable_iterator((Iterable *)l->d);
  while (iterator_move_next(i))
    object_free((Object *)iterator_current(i));
  object_free((Object *)i);
  object_free((Object *)l->d);
  free(l);
}

static bool linked_graph_adjacent(const Graph *g, const void *x,
                                  const void *y) {
  Set *s = dictionary_search(((LinkedGraph *)g)->d, x);
  return s == NULL ? false : set_search(s, y);
}

static const Set *linked_graph_vertices(const Graph *g) {
  return (Set *)((LinkedGraph *)g)->d;
}

static void linked_graph_insert_edge_directed(Graph *g, void *x, void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  Set *s = dictionary_search(l->d, x);
  if (s == NULL)
    dictionary_insert(l->d, x, s = l->f(l->user_data));
  set_insert(s, y);
}

static void linked_graph_insert_edge_undirected(Graph *g, void *x, void *y) {
  linked_graph_insert_edge_directed(g, x, y);
  linked_graph_insert_edge_directed(g, y, x);
}

static void linked_graph_delete_edge_directed(Graph *g, const void *x,
                                              const void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  Set *s = dictionary_search(l->d, x);
  set_delete(s, y);
  if (set_empty(s))
    dictionary_delete(l->d, x), free(s);
}

static void linked_graph_delete_edge_undirected(Graph *g, const void *x,
                                                const void *y) {
  linked_graph_delete_edge_directed(g, x, y);
  linked_graph_delete_edge_directed(g, y, x);
}

Graph *linked_graph_new(Hash h, graph_vtable *vtable) {
  static const size_t DEFAULT_CAPACITY = 11;
  LinkedGraph *l = malloc(sizeof(LinkedGraph));
  l->d = (Dictionary *)hashtable_new(contract_requires_non_null(h));
  l->vtable = vtable;
  l->e = 0;
  l->v = 0;
  l->f = (set_factory) hashtable_new;
  l->user_data = h;
  return (Graph *)l;
}

Graph *linked_graph_new_undirected(Hash h) {
  static graph_vtable vtable = {
    {.free = linked_graph_free },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .vertices = linked_graph_vertices,
        .insert_edge = linked_graph_insert_edge_undirected,
        .delete_edge = linked_graph_delete_edge_undirected
  };
  return linked_graph_new(h, &vtable);
}

Graph *linked_graph_new_directed(Hash h) {
  static graph_vtable vtable = {
    {.free = linked_graph_free },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .vertices = linked_graph_vertices,
        .insert_edge = linked_graph_insert_edge_directed,
        .delete_edge = linked_graph_delete_edge_directed
  };
  return linked_graph_new(h, &vtable);
}
