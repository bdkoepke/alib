#include "../math_extended.h"
#include "../test.h"
#include "algorithm.h"
#include "array.h"
#include "array_container.h"
#include "binary_tree.h"
#include "chapter_3_values.h"
#include "hashtable.h"
#include "linked_stack.h"
#include "red_black_tree.h"
#include "sort_int.h"
#include "sparse_array.h"
#include "stack.h"
#include "test_container.h"
#include "type.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool nested_parenthesis(const char *s, int *count) {
  size_t c = 0;
  size_t i;
  size_t length = strlen(s);
  for (i = 0; i < length; i++) {
    switch (s[i]) {
    case '(':
      c++;
      *count = i;
      break;
    case ')':
      if (c == 0) {
        *count = i;
        return false;
      }
      c--;
      break;
    default:
      continue;
    }
  }

  return c == 0;
}

void _test_array(void) {
  puts("test_array");
  Array *a = array_new();
  test_array(a, test_values, test_values_length);
  object_free((Object *)a);

  a = array_new();
  test_array(a, test_values_extended, test_values_extended_length);
  object_free((Object *)a);
}

void _test_linked_stack(void) {
  puts("test_linked_stack");
  LinkedStack *l = linked_stack_new();
  test_linked_stack(l, test_values, test_values_length);
  object_free((Object *)l);

  l = linked_stack_new();
  test_linked_stack(l, test_values_extended, test_values_extended_length);
  object_free((Object *)l);
}

void _test_queue(void) {
  puts("test_queue");
  Queue *q = queue_new();
  test_queue(q, test_values, test_values_length);
  object_free((Object *)q);

  q = queue_new();
  test_queue(q, test_values_extended, test_values_extended_length);
  object_free((Object *)q);
}

void test_binary_tree(void) {
  puts("test_binary_tree");
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  test_tree((Tree *)b, test_values, test_values_length, test_values_pre_order,
            test_values_in_order, test_values_post_order,
            test_values_level_order);
  object_free((Object *)b);

  b = binary_tree_new(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void test_red_black_tree(void) {
  puts("test_red_black_tree: not implemented");
/*  Tree *r = red_black_tree_new(compare_int_pointer);
  test_tree((Tree *)r, test_values, test_values_length, test_values_pre_order,
            test_values_in_order, test_values_post_order,
            test_values_level_order);
  object_free((Object *)r);

  r = red_black_tree_new(compare_int_pointer);
  test_dictionary((Dictionary *)r, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)r); */
}

void test_hashtable(void) {
  puts("test_hashtable");
  Container *c = hashtable_new(hash_int_pointer);
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);

  c = hashtable_new(hash_int_pointer);
  test_container(c, test_values_extended, test_values_extended_length);
  object_free((Object *)c);
}

void question_3_1(void) {
  puts("test_question_3_1");
  int count;
  assert_true(nested_parenthesis("((())())()", &count));
  assert_false(nested_parenthesis(")()(", &count));
  assert_equals(count, 0);
  assert_false(nested_parenthesis("()(", &count));
  assert_equals(count, 2);
}

void question_3_2(void) {
  puts("test_question_3_2");
  Stack *s = (Stack *)linked_stack_new();
  test_stack(s, test_values, test_values_length);
  test_stack(s, test_values_extended, test_values_extended_length);
  object_free((Object *)s);
}

void question_3_3(void) {
  puts("test_question_3_3");
  Array *a = array_new();
  test_container((Container *)a, test_values, test_values_length);
  object_free((Object *)a);
  a = array_new();
  test_container((Container *)a, test_values_extended,
                 test_values_extended_length);
  object_free((Object *)a);
}

void question_3_4(void) {
  puts("test_question_3_4");
  Container *c = (Container *)array_container_new(
      reduce_int(test_values, test_values_length, max, 0));
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);
  c = (Container *)array_container_new(
      reduce_int(test_values_extended_positive,
                 test_values_extended_positive_length, max, 0));
  test_container(c, test_values_extended_positive,
                 test_values_extended_positive_length);
  object_free((Object *)c);
}

void question_3_7(void) {
  puts("test_question_3_7");
  BinaryTree *b = binary_tree_new_fast_min_max(compare_int_pointer);
  test_tree((Tree *)b, test_values, test_values_length, test_values_pre_order,
            test_values_in_order, test_values_post_order,
            test_values_level_order);
  object_free((Object *)b);

  b = binary_tree_new_fast_min_max(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void question_3_8(void) {
  puts("test_question_3_8");
  SortedSet *s = sorted_set_new(compare_int_pointer);
  test_sorted_set(s, test_values, test_values_length);
  object_free((Object *)s);

  s = sorted_set_new(compare_int_pointer);
  test_sorted_set(s, test_values_extended, test_values_extended_length);
  object_free((Object *)s);
}

void question_3_9(void) {
  puts("test_question_3_9");
  BinaryTree *a = binary_tree_new(compare_int_pointer);
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < 10; i++)
    container_insert((Container *)a, INT_TO_POINTER(i));
  for (i; i < 20; i++)
    container_insert((Container *)b, INT_TO_POINTER(i));
  BinaryTree *concat = binary_tree_concat(a, b);
  for (i = 0; i < 20; i++)
    assert_equals(POINTER_TO_INT(
                      container_search((Container *)concat, INT_TO_POINTER(i))),
                  i);
  object_free((Object *)concat);
}

static size_t bin_packing_best_fit(const double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, (void *)&w[i]);

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
		double r = 1.0 - bin;
    double *predecessor = (double*)dictionary_predecessor((Dictionary *)b, &r);
		if (predecessor == NULL) {
      bins++;
      bin = 0;
    } else {
      bin += *predecessor;
      container_delete((Container *)b, predecessor);
    }
  }
  object_free((Object *)b);
  return bin == 0 ? bins : bins + 1;
}

static size_t bin_packing_worst_fit(const double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, (void *)&w[i]);

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    double *min = (double*)dictionary_min((Dictionary *)b);
    if (*min > (1 - bin)) {
      bins++;
      bin = 0;
    } else {
      bin += *min;
      container_delete((Container *)b, min);
    }
  }
  object_free((Object *)b);
  return bin == 0 ? bins : bins + 1;
}

void question_3_10(void) {
  puts("test_question_3_10");
	assert_equals(bin_packing_worst_fit(test_bin_packing_values, test_bin_packing_values_length), 63);
	assert_equals(bin_packing_best_fit(test_bin_packing_values, test_bin_packing_values_length), 52);
}

void question_3_11(void) {
	puts("test_question_3_11");
	RangeContainer *r = array_range_container_new(compare_int_pointer);
	test_range_container(r, test_values, test_values_length);
	object_free((Object *)r);

	r = array_range_container_new(compare_int_pointer);
	test_range_container(r, test_values_extended, test_values_extended_length);
	object_free((Object *)r);
}

void question_3_14(void) {
	puts("test_question_3_14: not implemented");
	PartialSum *p = partial_sum_new(compare_int_pointer);
	test_partial_sum(p, test_values, test_values_length);
	object_free((Object *)p);

	p = partial_sum_new(compare_int_pointer);
	test_partial_sum(p, test_values_extended, test_values_extended_length);
	object_free((Object *)p);
}

void question_3_15(void) {
  puts("test_question_3_15");
  Container *c =
      sparse_array_new(reduce_int(test_values, test_values_length, max, 0) + 1,
                       test_values_length);
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);

  c = sparse_array_new(
      reduce_int(test_values_extended_positive,
                 test_values_extended_positive_length, max, 0) + 1,
      test_values_extended_positive_length);
  test_container(c, test_values_extended_positive,
                 test_values_extended_positive_length);
  object_free((Object *)c);
}

void question_3_20(void) {
	puts("test_question_3_20");
	// completed in test_linked_stack
}

void question_3_21(void) {
	puts("test_question_3_21: not implemented");
}

void question_3_22(void) {
	puts("test_question_3_21: not implemented");
}

void question_3_23(void) {
	puts("test_question_3_23");
	// completed in test_linked_stack
}

void question_3_26(void) {
	puts("test_question_3_26: not implemented");
}

void question_3_27(void) {
	puts("test_question_3_27: not implemented");
}

static int *unordered_product_ignoring_index(const int *X, size_t length) {
	int number_of_products = log2(length);
	int *Y = malloc(sizeof(int) * length);
	int *M = malloc(sizeof(int) * length);
	Y = memcpy(Y, X, sizeof(int) * length);
	size_t i, j;
	for (i = 0; i < length; i++)
		for (j = 1; j < number_of_products; j++)
			Y[i] *= X[(i + j) % length];
	for (i = 0; i < length; i++) {
		M[i] = Y[(i + 1) % length];
		for (j = 1; j < (number_of_products - 1); j++)
			M[i] *= Y[(i + (j * number_of_products) + 1) % length];
		M[i] *= X[(i + (j * number_of_products) + 1) % length];
	}
	free(Y);
	return M;
}

void question_3_28(void) {
	puts("test_question_3_28");
	static int unordered[] = {6, 5, 3, 1, 7, 6, 2, 3};
	static size_t unordered_length = sizeof(unordered) / sizeof(int);
	static int expected[] = {3780, 4536, 7560, 22680, 3240, 3780, 11340, 7560};
	int *actual = unordered_product_ignoring_index(unordered, unordered_length);
	size_t i;
	for (i = 0; i < unordered_length; i++)
		assert_equals(actual[i], expected[i]);
	free(actual);
}

void chapter_3(void) {
  _test_array();
  _test_linked_stack();
  _test_queue();
  test_binary_tree();
	test_red_black_tree();
  test_hashtable();
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
  //question_3_8();
  question_3_9();
  question_3_10();
  //question_3_11();
  question_3_14();
  question_3_15();
	question_3_20();
	question_3_21();
	question_3_22();
	question_3_23();
	question_3_26();
	question_3_27();
	question_3_28();
}
