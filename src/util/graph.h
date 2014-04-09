#ifndef GRAPH_H
#define GRAPH_H

#include "../lang/object.h"
#include "set.h"

#include <stdbool.h>

typedef enum {
  Undiscovered,
  Discovered,
  Processed
} VertexState;

typedef struct _graph_vtable graph_vtable;
typedef struct {
  graph_vtable *vtable;
} Graph;
struct _graph_vtable {
  object_vtable object;
  bool (*adjacent)(const Graph *, const void *, const void *);
  const Set *(*neighbors)(const Graph *, const void *);
  const Set *(*vertices)(const Graph *);
  void (*insert_edge)(Graph *, void *, void *);
  void (*delete_edge)(Graph *, const void *, const void *);
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
const Set *graph_neighbors(const Graph *g, const void *x);

/**
 * Gets all vertices x in the graph.
 *
 * @param g the graph to get the vertices of.
 * @return a container containing the vertices.
 */
const Set *graph_vertices(const Graph *g);

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

#endif /* GRAPH_H */
