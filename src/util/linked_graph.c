#include "../diag/contract.h"
#include "edge_node.h"
#include "hashtable.h"
#include "linked_graph.h"
#include "linked_stack.h"

#include <stdlib.h>

typedef struct {
  graph_vtable *vtable;
  Container *h;
  size_t e, v;
} LinkedGraph;

void linked_graph_free(Object *o) {
  LinkedGraph *l = (LinkedGraph *)o;
  object_free((Object *)l->h);
  free(l);
}

static bool linked_graph_adjacent(const Graph *g, const void *x,
                                  const void *y) {
  EdgeNode *e = container_search(((LinkedGraph *)g)->h, &x);
  contract_requires(e);
  return e == NULL ? false : container_search((Container *)e, y);
}

static const Container *linked_graph_neighbors(const Graph *g, const void *x) {
  return container_search(((LinkedGraph *)g)->h, x);
}

static void linked_graph_insert_edge_directed(Graph *g, void *x, void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  EdgeNode *e = container_search(l->h, &x);
  if (e == NULL)
    container_insert(l->h, e = edge_node_new(x));
  container_insert((Container *)e, y);
}

static void linked_graph_insert_edge_undirected(Graph *g, void *x, void *y) {
  linked_graph_insert_edge_directed(g, x, y);
  linked_graph_insert_edge_directed(g, y, x);
}

static void linked_graph_delete_edge(Graph *g, const void *x, const void *y) {
  LinkedGraph *l = (LinkedGraph *)g;
  EdgeNode *e = container_search(l->h, &x);
  container_delete((Container *)e, y);
  if (container_empty((Container *)e))
    container_delete(l->h, e), free(e);
}

/*
static void *linked_graph_node_value(const Graph *g, const void *x) {}

static void linked_graph_set_node_value(Graph *g, void *x, void *a) {}

static void *linked_graph_edge_value(const Graph *g, const void *x,
                                     const void *y) {}

static void linked_graph_set_edge_value(Graph *g, void *x, void *y, void *a) {}
*/

Graph *linked_graph_new(Hash h, graph_vtable *vtable) {
  contract_requires(h != NULL);
  static const size_t DEFAULT_CAPACITY = 11;
  LinkedGraph *g = malloc(sizeof(LinkedGraph));
  g->vtable = vtable;
  g->e = 0;
  g->v = 0;
  g->h = hashtable_new(h);
  return (Graph *)g;
}

Graph *linked_graph_new_undirected(Hash h) {
  static graph_vtable vtable = {
    {.free = linked_graph_free },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .insert_edge = linked_graph_insert_edge_undirected,
        .delete_edge = linked_graph_delete_edge,
    /* .node_value = linked_graph_node_value, .set_node_value =
                                               linked_graph_set_node_value,
    .edge_value = linked_graph_edge_value, .set_edge_value =
                                               linked_graph_set_edge_value */
  };
  return linked_graph_new(h, &vtable);
}

Graph *linked_graph_new_directed(Hash h) {
  static graph_vtable vtable = {
    {.free = linked_graph_free },
        .adjacent = linked_graph_adjacent, .neighbors = linked_graph_neighbors,
        .insert_edge = linked_graph_insert_edge_directed,
        .delete_edge = linked_graph_delete_edge,
    /* .node_value = linked_graph_node_value, .set_node_value =
                                               linked_graph_set_node_value,
    .edge_value = linked_graph_edge_value, .set_edge_value =
                                               linked_graph_set_edge_value */
  };
  return linked_graph_new(h, &vtable);
}
