#ifndef GRAPH_H
#define GRAPH_H

#include "../lang/object.h"
#include "../util/container.h"

#include <stdbool.h>

typedef struct _graph_vtable graph_vtable;
typedef struct {
  graph_vtable *vtable;
} Graph;
struct _graph_vtable {
  object_vtable object;
  bool (*adjacent)(const Graph *, const void *, const void *);
  const Container *(*neighbors)(const Graph *, const void *);
  void (*insert_edge)(Graph *, void *, void *);
  void (*delete_edge)(Graph *, const void *, const void *);
  /* void *(*node_value)(const Graph *, const void *);
  void (*set_node_value)(Graph *, void *, void *);
  void *(*edge_value)(const Graph *, const void *, const void *);
  void (*set_edge_value)(Graph *, void *, void *, void *); */
};

/**
 * Tests whether there is an edge from node x to node y.
 *
 * @param g the graph to test the edge in.
 * @param x the first node.
 * @param y the second node.
 * @return true if there is an edge, false otherwise.
 */
bool graph_adjacent(const Graph *g, const void *x, const void *y);

/**
 * Lists all nodes y such that there is an edge from x to y.
 *
 * @param g the graph to list the nodes in.
 * @param x the node to search for edges on.
 * @return all nodes y such that there is an edge from x to y.
 */
const Container *graph_neighbors(const Graph *g, const void *x);

/**
 * Inserts the specified edge into the graph.
 *
 * @param g the graph to insert the edge into.
 * @param x the first point of the edge.
 * @param y the second point of the edge.
 */
void graph_insert_edge(Graph *g, void *x, void *y);

/**
 * Deletes the specified edge from the graph.
 *
 * @param g the graph to delete the edge from.
 * @param x the first point of the edge.
 * @parm y the second point of the edge.
 */
void graph_delete_edge(Graph *g, const void *x, const void *y);

/**
 * Gets the value associated with the node x.
 *
 * @param g the graph to get the value from.
 * @param x the node to get the value of.
 * @return null if there is no such x, the value otherwise.
void *graph_node_value(const Graph *g, const void *x);

 * Sets the value associated with the node x.
 *
 * @param g the graph to set the value in.
 * @param x the node to set the value of.
 * @param a the value.
void graph_set_node_value(Graph *g, void *x, void *a);

 * Gets the value associated with the edge x and y.
 *
 * @param g the graph to get the value from.
 * @param x the first node.
 * @param y the second node.
 * @return null if there is no such edge, the value otherwise.
void *graph_edge_value(const Graph *g, const void *x, const void *y);

 * Sets the value associated with the node x.
 *
 * @param g the graph to set the value in.
 * @param x the node to set the value of.
 * @param a the value.
void graph_set_edge_value(Graph *g, void *x, void *y, void *a);
 */

#endif /* GRAPH_H */
