#ifndef GRAPH_ITERATOR_H
#define GRAPH_ITERATOR_H

#include "../lang/object.h"
#include "edge_node.h"

typedef struct _graph_iterator_vtable graph_iterator_vtable;
typedef struct GraphIterator {
  graph_iterator_vtable *vtable;
} GraphIterator;
struct _graph_iterator_vtable {
  object_vtable object;
  EdgeNode *(*current_edge)(const GraphIterator *);
  void *(*current_vertex)(const GraphIterator *);
  bool (*move_next_edge)(GraphIterator *);
  bool (*move_next_vertex)(GraphIterator *);
};

/**
 * Gets the current graph iterator vertex.
 *
 * @param g the graph iterator.
 * @return the current graph iterator vertex.
 */
EdgeNode *graph_iterator_current_edge(const GraphIterator *g);

/**
 * Gets the current graph iterator vertex.
 *
 * @param g the graph iterator.
 * @return the current graph iterator vertex.
 */
void *graph_iterator_current_vertex(const GraphIterator *g);

/**
 * Moves the graph iterator to the next vertex.
 *
 * @param g the graph iterator to advance.
 * @return true if there is another vertex, false otherwise.
 */
bool graph_iterator_move_next_vertex(GraphIterator *g);

/**
 * Moves the graph iterator to the next edge node.
 *
 * @param g the graph iterator to advance.
 * @return true if there is another edge for the current
 *   vertex, false otherwise.
 */
bool graph_iterator_move_next_edge(GraphIterator *g);

EdgeNode *_graph_iterator_current_edge_invalid_state(const GraphIterator *g);
void *_graph_iterator_current_vertex_invalid_state(const GraphIterator *g);
bool _graph_iterator_move_next_vertex_invalid_state(GraphIterator *g);
bool _graph_iterator_move_next_edge_invalid_state(GraphIterator *g);

#endif /* GRAPH_ITERATOR_H */
