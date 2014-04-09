#include "../diag/contract.h"
#include "edge_node.h"
#include "hashtable.h"
#include "linked_graph.h"
#include "linked_stack.h"

#include <stdlib.h>

typedef Container *(*container_factory)();

typedef struct {
  graph_vtable *vtable;
  Dictionary *d;
  size_t e, v;
  container_factory f;
} LinkedGraph;

void linked_graph_free(Object *o) {
  LinkedGraph *l = (LinkedGraph *)o;
  /*
   Iterator *i = iterable_iterator((Iterable *)l->d);
   while (iterator_move_next(i))
     object_free(
         (Object *)container_delete((Container *)l->d, iterator_current(i)));
 	*/
  puts("memory leak");
  object_free((Object *)l->d);
  free(l);
}

static bool linked_graph_adjacent(const Graph *g, const void *x,
                                  const void *y) {
  Container *c = container_search((Container *)((LinkedGraph *)g)->d, x);
  return c == NULL ? false : container_search(c, y);
}

static const Container *linked_graph_neighbors(const Graph *g, const void *x) {
  return container_search((Container *)((LinkedGraph *)g)->d, x);
}

static const Container *linked_graph_vertices(const Graph *g) {
  return (Container *)((LinkedGraph *)g)->d;
}

static void linked_graph_insert_edge_directed(Graph *g, void *x, void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  Container *c = container_search((Container *)l->d, x);
  if (c == NULL)
    dictionary_insert(l->d, x, c = l->f());
  container_insert(c, y);
}

static void linked_graph_insert_edge_undirected(Graph *g, void *x, void *y) {
  linked_graph_insert_edge_directed(g, x, y);
  linked_graph_insert_edge_directed(g, y, x);
}

static void linked_graph_delete_edge_directed(Graph *g, const void *x,
                                              const void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  Container *c = container_search((Container *)l->d, x);
  container_delete(c, y);
  if (container_empty(c))
    container_delete((Container *)l->d, x), free(c);
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
  l->f = (container_factory) linked_stack_new;
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
