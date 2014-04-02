#include "linked_graph.h"

#include <stdlib.h>

typedef struct {
	const void *y;
	struct EdgeNode *n;
} EdgeNode;

typedef struct {
	graph_vtable *vtable;
	EdgeNode **edges;
	size_t e, v, capacity;
} LinkedGraph;

void linked_graph_free(Object *o) {
	LinkedGraph *l = (LinkedGraph *)o;
	free(l->edges);
	free(l);
}

static bool linked_graph_adjacent(const Graph *g, const void *x, const void *y) {
}

static void linked_graph_neighbors(const Graph *g, const void *x) {
}

static void linked_graph_insert_edge(Graph *g, void *x, void *y) {
}

static void linked_graph_delete_edge(Graph *g, const void *x, const void *y) {
}

static void *linked_graph_node_value(const Graph *g, const void *x) {
}

static void linked_graph_set_node_value(Graph *g, void *x, void *a) {
}

static void *linked_graph_edge_value(const Graph *g, const void *x, const void *y) {
}

static void linked_graph_set_edge_value(Graph *g, void *x, void *y, void *a) {
}

Graph *linked_graph_new() {
	static graph_vtable vtable = {
		{ .free = linked_graph_free },
		.adjacent = linked_graph_adjacent,
		.neighbors = linked_graph_neighbors,
		.insert_edge = linked_graph_insert_edge,
		.delete_edge = linked_graph_delete_edge,
		.node_value = linked_graph_node_value,
		.set_node_value = linked_graph_set_node_value,
		.edge_value = linked_graph_edge_value,
		.set_edge_value = linked_graph_set_edge_value
	};

	static const size_t DEFAULT_CAPACITY = 11;

	LinkedGraph *g = malloc(sizeof(LinkedGraph));
	g->vtable = &vtable;
	g->capacity = DEFAULT_CAPACITY;
	g->e = 0;
	g->v = 0;
	g->edges = malloc(sizeof(EdgeNode) * g->capacity);
	return (Graph *)g;
}
