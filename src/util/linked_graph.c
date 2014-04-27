#include "../diag/contract.h"
#include "edge_node.h"
#include "hashtable.h"
#include "linked_graph.h"

#include <stdlib.h>

typedef struct {
  Hash h;
  Equals e;
} HashEqualsPair;

typedef struct {
  graph_vtable *vtable;
  Dictionary *d;
  HashEqualsPair p;
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
  return (Set *)(((LinkedGraph *)g)->d);
}

static void linked_graph_insert_edge_directed(Graph *g, void *x, void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  Set *s = dictionary_search(l->d, x);
  if (s == NULL)
    dictionary_insert(l->d, x, s = (Set *)hashtable_new(l->p.h, l->p.e));
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
    object_free((Object *)dictionary_delete(l->d, x));
}

static void linked_graph_delete_edge_undirected(Graph *g, const void *x,
                                                const void *y) {
  linked_graph_delete_edge_directed(g, x, y);
  linked_graph_delete_edge_directed(g, y, x);
}

static Graph *linked_graph_new(Hash h, Equals e, graph_vtable *vtable) {
  static const size_t DEFAULT_CAPACITY = 11;
  LinkedGraph *l = malloc(sizeof(LinkedGraph));
  l->d = (Dictionary *)hashtable_new(contract_requires_non_null(h),
                                     contract_requires_non_null(e));
  l->vtable = vtable;
  l->p.h = h;
  l->p.e = e;
  return (Graph *)l;
}

UndirectedGraph *undirected_linked_graph_new(Hash h, Equals e) {
  static graph_vtable vtable = {
    {.class = "linked_graph", .free = linked_graph_free,
                                  .to_string = _object_to_string },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .vertices = linked_graph_vertices,
        .insert_edge = linked_graph_insert_edge_undirected,
        .delete_edge = linked_graph_delete_edge_undirected,
  };
  return (UndirectedGraph *)linked_graph_new(h, e, &vtable);
}

DirectedGraph *directed_linked_graph_new(Hash h, Equals e) {
  static graph_vtable vtable = {
    {.class = "linked_graph", .free = linked_graph_free,
                                  .to_string = _object_to_string },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .vertices = linked_graph_vertices,
        .insert_edge = linked_graph_insert_edge_directed,
        .delete_edge = linked_graph_delete_edge_directed,
  };
  return (DirectedGraph *)linked_graph_new(h, e, &vtable);
}
