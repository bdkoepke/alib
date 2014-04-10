#include "chapter_5.h"
#include "lang/hash.h"
#include "lang/type.h"
#include "util/linked_graph.h"
#include "util/matrix_graph.h"
#include "test/test.h"

void test_linked_graph(void) {
  puts("test_linked_graph");
  Graph *g = linked_graph_new_directed(hash_int_pointer);
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
	/*
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++) {
      graph_delete_edge(g, INT_TO_POINTER(i),
                        INT_TO_POINTER(graph[i - 1][j - 1]));
      assert_false(graph_adjacent(g, INT_TO_POINTER(i),
                                  INT_TO_POINTER(graph[i - 1][j - 1])));
    } */
  object_free((Object *)g);
}

void test_matrix_graph(void) {}
