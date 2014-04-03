#include "chapter_5.h"
#include "lang/hash.h"
#include "lang/type.h"
#include "util/linked_graph.h"
#include "util/matrix_graph.h"

void test_linked_graph(void) {
  puts("test_linked_graph");
  Graph *g = linked_graph_new_undirected(hash_int_pointer);
  int graph[][7] = { { 2, 5 }, { 1, 3, 5 }, { 2, 4 }, { 3, 5, 6 }, { 1, 2, 4 },
                     { 4 } };
  int i, j;
  for (i = 1; i <= 6; i++) {
    printf("vertex %d\n", i);
    for (j = 0; j < 7 && graph[i - 1][j]; j++)
      printf("%6s %d\n", "edge:", graph[i - 1][j]);
  }
  for (i = 1; i <= 6; i++) {
    printf("vertex %d\n", i);
    for (j = 0; j < 7 && graph[i - 1][j]; j++) {
      printf("%6s %d\n", "edge:", graph[i - 1][j]);
      graph_insert_edge(g, INT_TO_POINTER(i), INT_TO_POINTER(graph[i - 1][j]));
    }
  }

  puts("");
  object_free((Object *)g);
}

void test_matrix_graph(void) {}
