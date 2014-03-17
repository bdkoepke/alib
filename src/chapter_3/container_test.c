#include "algorithm.h"
#include "container_test.h"
#include "test.h"
#include "type.h"

void test_array(Array *a, const int *values, size_t length) {}

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
	int min = reduce(values, length, min, 0);
	int max = reduce(values, length, max, 0);
}

void test_graph(Graph *g, const int *values, size_t length) {}

void test_priority_queue(PriorityQueue *p, const int *values, size_t length) {}

void test_queue(Queue *q, const int *values, size_t length) {
	test_container((Container *)q, values, length);
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
