#include "algorithm.h"
#include "compare.h"
#include "test_container.h"
#include "sort_int.h"
#include "string.h"
#include "test.h"
#include "type.h"

#include <assert.h>
#include <stdlib.h>

void test_array(Array *a, const int *values, size_t length) {}

static int _compare_int(const void *a, const void *b) {
	return *((int*)a) - *((int*)b);
}

void test_container(Container *c, const int *values, size_t length) {
  assert_true(container_empty(c));
  size_t i;
  for (i = 0; i < length; i++) {
    container_insert(c, INT_TO_POINTER(values[i]));
    assert_equals(
        POINTER_TO_INT(container_search(c, INT_TO_POINTER(values[i]))),
        values[i]);
  }
  assert_false(container_empty(c));
  for (i = 0; i < length; i++) {
    container_delete(c, INT_TO_POINTER(values[i]));
    assert_equals(
        POINTER_TO_INT(container_search(c, INT_TO_POINTER(values[i]))), 0);
  }
  assert_true(container_empty(c));
}

void test_dictionary(Dictionary *d, const int *values, size_t length) {
  test_container((Container *)d, values, length);
  int *sorted = sort_int(values, length);

  size_t i;
  for (i = 0; i < length; i++)
    container_insert((Container *)d, INT_TO_POINTER(values[i]));

  assert_equals(POINTER_TO_INT(dictionary_min(d)), sorted[0]);
  assert_equals(POINTER_TO_INT(dictionary_max(d)), sorted[length - 1]);

  for (i = 0; i < length; i++) {
    int j = binary_search(&values[i], sorted, length, sizeof(int), _compare_int);
    int predecessor = (j == 0 ? 0 : sorted[j - 1]);
    assert_equals(
        POINTER_TO_INT(dictionary_predecessor(d, INT_TO_POINTER(values[i]))),
        predecessor);
  }
  for (i = 0; i < length; i++) {
    int j = binary_search(&values[i], sorted, length, sizeof(int), _compare_int);
    int successor = (j == (length - 1) ? 0 : sorted[j + 1]);
    assert_equals(
        POINTER_TO_INT(dictionary_successor(d, INT_TO_POINTER(values[i]))),
        successor);
  }

  free(sorted);
}

void test_graph(Graph *g, const int *values, size_t length) {}

void test_priority_queue(PriorityQueue *p, const int *values, size_t length) {}

void test_queue(Queue *q, const int *values, size_t length) {
  test_container((Container *)q, values, length);
}

void test_sorted_set(SortedSet *s, const int *values, size_t length) {
  assert_true(sorted_set_empty(s));
  size_t i;
  for (i = 0; i < length; i++) {
    sorted_set_insert(s, INT_TO_POINTER(values[i]));
    assert_true(sorted_set_member(s, INT_TO_POINTER(values[i])));
  }
  assert_false(sorted_set_empty(s));
  int *sorted = sort_int(values, length);
  for (i = 0; i < length; i++) {
    assert_true(sorted_set_member(s, INT_TO_POINTER(sorted[i])));
    assert_equals(POINTER_TO_INT(sorted_set_delete(s, 0)), sorted[i]);
    assert_false(sorted_set_member(s, INT_TO_POINTER(sorted[i])));
  }
  assert_true(sorted_set_empty(s));
  object_free((Object *)s);
  free(sorted);
}

void test_stack(Stack *s, const int *values, size_t length) {
  Container *c = (Container *)s;
  assert_true(container_empty(c));
  size_t i;
  for (i = 0; i < length; i++) {
    container_insert(c, INT_TO_POINTER(values[i]));
    assert_equals(
        POINTER_TO_INT(container_search(c, INT_TO_POINTER(values[i]))),
        values[i]);
  }
  assert_false(container_empty(c));
  stack_reverse(s);
  for (i = 0; i < length; i++)
    assert_equals(POINTER_TO_INT(stack_pop(s)), values[i]);
}

void test_tree(Tree *t, const int *values, size_t length) {}
