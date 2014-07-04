#include "diag/contract.h"
#include "chapter_5.h"
#include "lang/hash.h"
#include "lang/math_extended.h"
#include "lang/type.h"
#include "util/graph_visitor.h"
#include "util/hashtable.h"
#include "util/linked_queue.h"
#include "util/linked_graph.h"
#include "util/matrix_graph.h"
#include "test/test.h"
#include "lang/unsafe.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  Undiscovered,
  Discovered,
  Processed
} VertexState;
static const VertexState undiscovered = Undiscovered;
static const VertexState discovered = Discovered;
static const VertexState processed = Processed;

typedef struct {
  const void *u;
  const void *v;
} Edge;
Edge *edge_new(const void *u, const void *v) {
  Edge *e = malloc(sizeof(Edge));
  e->u = u;
  e->v = v;
  return e;
}
bool edge_equals(const void *_u, const void *_v) {
  Edge *u = (Edge *)_u, *v = (Edge *)_v;
  return (equals_int_pointer(u->u, v->u) && equals_int_pointer(u->v, v->v)) ||
         (equals_int_pointer(u->u, v->v) && equals_int_pointer(u->v, v->u));
}
size_t edge_hash(const void *x) {
  Edge *e = (Edge *)x;
  return (hash_int_pointer(e->u) + hash_int_pointer(e->v) + 17 * 31) * 31 *
         max(POINTER_TO_INT(e->u) / POINTER_TO_INT(e->v),
             POINTER_TO_INT(e->v) / POINTER_TO_INT(e->u));
}

static void print_vertex_early(GraphVisitor *gv, const void *v) {
  printf("processed vertex early %d\n", POINTER_TO_INT(v));
}
static void print_edge(GraphVisitor *gv, const void *x, const void *y) {
  printf("processed edge (%d,%d)\n", POINTER_TO_INT(x), POINTER_TO_INT(y));
}
static void print_vertex_late(GraphVisitor *gv, const void *v) {
  printf("processed vertex late: %d\n", POINTER_TO_INT(v));
}
static graph_visitor_vtable graph_visitor_print_vtable = {
  .vertex_early = print_vertex_early,
  .edge = print_edge,
  .vertex_late = print_vertex_late
};

void graph_breadth_first(const Graph *g, const void *s, GraphVisitor *gv) {
  Dictionary *vertices =
      (Dictionary *)hashtable_new(hash_int_pointer, equals_int_pointer);
  Dictionary *parents =
      (Dictionary *)hashtable_new(hash_int_pointer, equals_int_pointer);
  Dictionary *edges = (Dictionary *)hashtable_new(edge_hash, edge_equals);

  Iterator *i = iterable_iterator((Iterable *)graph_vertices(g));
  while (iterator_move_next(i)) {
    dictionary_insert(vertices, iterator_current(i), const_cast(&undiscovered));
    dictionary_insert(parents, iterator_current(i), NULL);
  }
  object_free((Object *)i);
  contract_requires_non_null(dictionary_search(vertices, s));
  dictionary_reassign(vertices, s, const_cast(&discovered));

  Queue *q = linked_queue_new();
  queue_enqueue(q, const_cast(s));
  while (!container_empty((Container *)q)) {
    const void *u = queue_dequeue(q);
    graph_visitor_vertex_early(gv, u);
    i = iterable_iterator((Iterable *)graph_neighbors(g, u));
    while (iterator_move_next(i)) {
      const void *v = iterator_current(i);
      Edge *e = edge_new(const_cast(u), const_cast(v));
      if (dictionary_search(edges, e) == INT_TO_POINTER(NULL))
        graph_visitor_edge(gv, u, v),
            dictionary_insert(edges, e, INT_TO_POINTER(true));
      else
        free(e);
      if (dictionary_search(vertices, v) == &undiscovered) {
        dictionary_reassign(vertices, v, const_cast(&discovered));
        dictionary_reassign(parents, v, const_cast(u));
        queue_enqueue(q, const_cast(v));
      }
    }
    object_free((Object *)i);
    graph_visitor_vertex_late(gv, u);
    dictionary_reassign(vertices, u, const_cast(&processed));
  }
  object_free((Object *)q);
  object_free((Object *)vertices);
  object_free((Object *)parents);
  i = iterable_iterator((Iterable *)edges);
  while (iterator_move_next(i))
    free(iterator_current(i));
  object_free((Object *)i);
  object_free((Object *)edges);
}

void test_linked_graph(void) {
  puts("test_linked_graph");
  DirectedGraph *g =
      directed_linked_graph_new(hash_int_pointer, equals_int_pointer);
  int graph[][6] = {
    { 2, 5, 6 }, { 1, 3, 5 }, { 2, 4 }, { 3, 5 }, { 1, 2, 4 }, { 1 }
  };

  int i, j;
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++) {
      graph_insert_edge(g, INT_TO_POINTER(i),
                        INT_TO_POINTER(graph[i - 1][j - 1]));
      assert_true(graph_adjacent(g, INT_TO_POINTER(i),
                                 INT_TO_POINTER(graph[i - 1][j - 1])));
    }
  // verify that the insertion worked correctly
  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++)
      assert_true(graph_adjacent(g, INT_TO_POINTER(i),
                                 INT_TO_POINTER(graph[i - 1][j - 1])));
  // verify set operations
  for (i = 1; i <= 6; i++) {
    const Set *s = graph_neighbors(g, INT_TO_POINTER(i));
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++)
      assert_equals(
          POINTER_TO_INT(set_search(s, INT_TO_POINTER(graph[i - 1][j - 1]))),
          graph[i - 1][j - 1]);
  }

  GraphVisitor gv = { .vtable = &graph_visitor_print_vtable };
  graph_breadth_first(g, INT_TO_POINTER(1), &gv);

  /*
void find_path(int start, int end, int parents[]) {
if ((start == end) || (end == POINTER_TO_INT(NULL)))
printf("\n%d", start);
else
find_path(start, parents[end - 1], parents), printf(" %d", end);
}

Iterator *it = iterable_iterator((Iterable *)parents);
int p[6];
i = 0;
while (iterator_move_next(it))
p[i++] = POINTER_TO_INT(dictionary_search(parents, iterator_current(it)));
for (i = 0; i < 6; i++)
printf("%d\n", p[i]);

find_path(1, 4, p);
  */

  for (i = 1; i <= 6; i++)
    for (j = 1; j <= 6 && graph[i - 1][j - 1]; j++) {
      graph_delete_edge(g, INT_TO_POINTER(i),
                        INT_TO_POINTER(graph[i - 1][j - 1]));
      assert_false(graph_adjacent(g, INT_TO_POINTER(i),
                                  INT_TO_POINTER(graph[i - 1][j - 1])));
    }
  object_free((Object *)g);
}

void test_matrix_graph(void) {}
