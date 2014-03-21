#include "../util/compare.h"
#include "../lang/type.h"
#include "../lang/algorithm.h"
#include "test_container.h"
#include "../lang/sort_int.h"
#include "../lang/string.h"
#include "test.h"

#include <assert.h>
#include <stdlib.h>

void test_array(Array *a, const int *values, size_t length) {
  test_container((Container *)a, values, length);
  assert_true(container_empty((Container *)a));
  size_t i;
  for (i = 0; i < length; i++) {
    assert_equals(array_size(a), i);
    container_insert((Container *)a, INT_TO_POINTER(values[i]));
    assert_equals(POINTER_TO_INT(container_search((Container *)a,
                                                  INT_TO_POINTER(values[i]))),
                  values[i]);
    assert_false(container_empty((Container *)a));
  }
  assert_equals(array_size(a), length);
  for (i = 0; i < length; i++)
    array_set(a, i, NULL);
  for (i = 0; i < length; i++)
    assert_equals(POINTER_TO_INT(array_get(a, i)), POINTER_TO_INT(NULL));
  for (i = 0; i < length; i++)
    container_delete((Container *)a, NULL);
  assert_true(container_empty((Container *)a));
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
    int j = binary_search(&values[i], sorted, length, sizeof(int), compare_int);
    int predecessor = (j == 0 ? 0 : sorted[j - 1]);
    assert_equals(
        POINTER_TO_INT(dictionary_predecessor(d, INT_TO_POINTER(values[i]))),
        predecessor);
  }
  for (i = 0; i < length; i++) {
    int j = binary_search(&values[i], sorted, length, sizeof(int), compare_int);
    int successor = (j == (length - 1) ? 0 : sorted[j + 1]);
    assert_equals(
        POINTER_TO_INT(dictionary_successor(d, INT_TO_POINTER(values[i]))),
        successor);
  }

  while (!container_empty((Container *)d))
    container_delete((Container *)d, dictionary_min(d));

  free(sorted);
}

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
    assert_true(sorted_set_size(s) == (i + 1));
  }
  assert_false(sorted_set_empty(s));
  int *sorted = sort_int(values, length);
  size_t size = length;
  for (i = 0; i < length; i++) {
    assert_true(sorted_set_member(s, INT_TO_POINTER(sorted[i])));
    assert_equals(POINTER_TO_INT(sorted_set_delete(s, 0)), sorted[i]);
    assert_false(sorted_set_member(s, INT_TO_POINTER(sorted[i])));
    size--;
    assert_true(sorted_set_size(s) == size);
  }
  assert_true(sorted_set_empty(s));
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
  int j;
  for (j = (length - 1); j >= 0; j--)
    assert_equals(POINTER_TO_INT(stack_pop(s)), values[j]);
  assert_true(container_empty(c));
}

void test_linked_stack(LinkedStack *l, const int *values, size_t length) {
  test_stack((Stack *)l, values, length);
  Container *c = (Container *)l;
  assert_true(container_empty(c));
  size_t i;
  for (i = 0; i < length; i++) {
    container_insert(c, INT_TO_POINTER(values[i]));
    assert_equals(
        POINTER_TO_INT(container_search(c, INT_TO_POINTER(values[i]))),
        values[i]);
  }
  assert_false(container_empty(c));
  assert_equals(linked_stack_middle(l),
                even(length) ? length / 2 : length / 2 + 1);
  linked_stack_reverse(l);
  for (i = 0; i < length; i++)
    assert_equals(POINTER_TO_INT(stack_pop((Stack *)l)), values[i]);
  assert_true(container_empty(c));
}

typedef struct {
  object_vtable *vtable;
  const int *order;
  size_t i;
} OrderVisitor;

static void order_visitor_free(Object *o) { free(o); }

static OrderVisitor *order_visitor_new(const int *order) {
  static object_vtable vtable = {.free = order_visitor_free };

  OrderVisitor *o = malloc(sizeof(OrderVisitor));
  o->vtable = &vtable;
  o->order = order;
  o->i = 0;
  return o;
}

static void order_visitor_visit(void *p, void *x) {
  OrderVisitor *o = (OrderVisitor *)p;
  assert_equals(POINTER_TO_INT(x), o->order[o->i++]);
}

void test_tree(Tree *t, const int *values, size_t length, const int *pre_order,
               const int *in_order, const int *post_order,
               const int *level_order) {
  test_dictionary((Dictionary *)t, values, length);
  assert_true(container_empty((Container *)t));

  size_t i;
  for (i = 0; i < length; i++)
    container_insert((Container *)t, INT_TO_POINTER(values[i]));

  OrderVisitor *o = order_visitor_new(pre_order);
  tree_pre_order(t, order_visitor_visit, o);
  object_free((Object *)o);

  o = order_visitor_new(in_order);
  tree_in_order(t, order_visitor_visit, o);
  object_free((Object *)o);

  o = order_visitor_new(post_order);
  tree_post_order(t, order_visitor_visit, o);
  object_free((Object *)o);

  o = order_visitor_new(level_order);
  tree_level_order(t, order_visitor_visit, o);
  object_free((Object *)o);
}

void test_partial_sum(PartialSum *p, const int *values, const size_t length) {}

void test_range_container(RangeContainer *r, const int *values,
                          const size_t length) {
  size_t i;
  for (i = 0; i < length; i++)
    range_container_insert(r, INT_TO_POINTER(values[i]));
}

void test_heap_empty(Heap *h, const int *values, const size_t length) {
  assert_true(heap_empty(h));

  int *sorted = sort_int(values, length);
  size_t i;
  for (i = 0; i < length; i++)
    heap_insert(h, INT_TO_POINTER(values[i]));

  free(sorted);
  test_heap(h, values, length);
}

void test_heap(Heap *h, const int *values, const size_t length) {
  assert_false(heap_empty(h));

  int *sorted = sort_int(values, length);
  size_t i;
  for (i = 0; i < length; i++)
    assert_equals(POINTER_TO_INT(heap_extract_min(h)), sorted[i]);

  assert_true(heap_empty(h));
  free(sorted);
}
