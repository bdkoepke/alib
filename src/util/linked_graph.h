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
UndirectedGraph *undirected_linked_graph_new(Hash, Equals);

/**
 * Creates a new linked graph.
 * 
 * @return a new linked graph.
 */
DirectedGraph *directed_linked_graph_new(Hash, Equals);

#endif /* LINKED_GRAPH_H */
