#ifndef LINKED_GRAPH_H
#define LINKED_GRAPH_H

#include "../lang/hash.h"
#include "graph.h"

#include <stddef.h>

/**
 * Creates a new linked graph.
 * 
 * @return a new linked graph.
 */
Graph *linked_graph_new_undirected(Hash);
/**
 * Creates a new linked graph.
 * 
 * @return a new linked graph.
 */
Graph *linked_graph_new_directed(Hash);

#endif /* LINKED_GRAPH_H */
