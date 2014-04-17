#include "diag/contract.h"
#include "chapter_5.h"
#include "lang/hash.h"
#include "lang/type.h"
#include "util/hashtable.h"
#include "util/linked_queue.h"
#include "util/linked_graph.h"
#include "util/matrix_graph.h"
#include "test/test.h"
#include "lang/unsafe.h"

#include <stdio.h>

void BFS(const Graph *g, const void *s, void (*process_vertex_early)(const void *), void (*process_edge)(const void *, const void *), void (*process_vertex_late)(const void *), Hash h) {
	typedef enum {
		Undiscovered,
		Discovered,
		Processed
	} VertexState;
	static const VertexState undiscovered = Undiscovered;
	static const VertexState discovered = Discovered;
	static const VertexState processed = Processed;

	Dictionary *states = (Dictionary *)hashtable_new(h);
	Dictionary *parents = (Dictionary *)hashtable_new(h);

	Iterator *i = iterable_iterator((Iterable *)graph_vertices(g));
	while (iterator_move_next(i)) {
		dictionary_insert(states, iterator_current(i), const_cast(&undiscovered));
		dictionary_insert(parents, iterator_current(i), NULL);
	}
	contract_requires_non_null(dictionary_search(states, s));
	dictionary_reassign(states, s, const_cast(&discovered));

	Queue *q;
	queue_enqueue(q = linked_queue_new(), (void *)s);

	while (! container_empty((Container *)q)) {
		const void *u = queue_dequeue(q);
		process_vertex_early(u);
		i = iterable_iterator((Iterable *)graph_neighbors(g, u));
		while (iterator_move_next(i)) {
			const void *v = iterator_current(i);
			process_edge(u, v);
			if (dictionary_search(states, v) == &undiscovered) {
				dictionary_reassign(states, v, (void *)&discovered);
				dictionary_reassign(parents, v, (void *)u);
				queue_enqueue(q, (void *)v);
			}
		}
		process_vertex_late(u);
		dictionary_reassign(states, u, const_cast(&processed));
	}
}

void test_linked_graph(void) {
  puts("test_linked_graph");
  DirectedGraph *g = directed_linked_graph_new(hash_int_pointer);
  int graph[][6] = { { 2, 5 }, { 1, 3, 5 }, { 2, 4 }, { 3, 5, 6 }, { 1, 2, 4 },
                     { 4 } };
  int i, j;
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++) {
      graph_insert_edge(g, INT_TO_POINTER(i),
                        INT_TO_POINTER(graph[i - 1][j - 1]));
      assert_true(graph_adjacent(g, INT_TO_POINTER(i),
                                 INT_TO_POINTER(graph[i - 1][j - 1])));
    }
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++)
      assert_true(graph_adjacent(g, INT_TO_POINTER(i),
                                 INT_TO_POINTER(graph[i - 1][j - 1])));
  for (i = 1; i <= 6; i++) {
    const Set *s = graph_neighbors(g, INT_TO_POINTER(i));
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++)
      assert_equals(
          POINTER_TO_INT(set_search(s, INT_TO_POINTER(graph[i - 1][j - 1]))),
          graph[i - 1][j - 1]);
  }

	void process_vertex_early(const void *v) {
		printf("processed vertex early %d\n", v);
	}
	void process_edge(const void *x, const void *y) {
		printf("processed edge (%d,%d)\n", x, y);
	}
	void process_vertex_late(const void *v) {
		printf("processed vertex late: %d\n", v);
	}

	BFS(g, INT_TO_POINTER(1), process_vertex_early, process_edge, process_vertex_late, hash_int_pointer);

	/*
	const Set *vertices = graph_vertices(g);

	Iterator *it = iterable_iterator((Iterable *)vertices);
	while (iterator_move_next(it))
		printf("%d\n", iterator_current(it));
	
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++) {
      graph_delete_edge(g, INT_TO_POINTER(i),
                        INT_TO_POINTER(graph[i - 1][j - 1]));
      assert_false(graph_adjacent(g, INT_TO_POINTER(i),
                                  INT_TO_POINTER(graph[i - 1][j - 1])));
    }
  object_free((Object *)g);
	*/
}

void test_matrix_graph(void) {}
