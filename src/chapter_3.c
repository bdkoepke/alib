#include "lang/algorithm.h"
#include "lang/math_extended.h"
#include "lang/sort_int.h"
#include "lang/type.h"
#include "test/test.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
#include "util/array.h"
#include "util/array_container.h"
#include "util/binary_tree.h"
#include "util/hashtable.h"
#include "util/linked_stack.h"
#include "util/node.h"
#include "util/red_black_tree.h"
#include "util/sparse_array.h"
#include "util/stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const double test_bin_packing_values[] = {
  0.3362347542, 0.3178301298, 0.6860678412, 0.7340748264, 0.1900018821,
  0.984185261, 0.0281661723, 0.6661597076, 0.6800948414, 0.7188397606,
  0.0860246283, 0.4094339397, 0.2783007051, 0.6902901942, 0.2631758486,
  0.5286753045, 0.7999930265, 0.7275710572, 0.963349744, 0.2755393689,
  0.5613411679, 0.855369739, 0.1771981616, 0.6169994571, 0.5694481058,
  0.7549725035, 0.8177760153, 0.3599889043, 0.0442691229, 0.9314259891,
  0.4850223095, 0.8299687761, 0.8190858914, 0.1444724957, 0.0456538093,
  0.0205221248, 0.400213286, 0.663251318, 0.4663875755, 0.1214011144,
  0.2012233047, 0.9519117968, 0.7384792918, 0.0222310086, 0.436982126,
  0.3443846819, 0.7886456463, 0.7097351854, 0.0010258025, 0.5920229102,
  0.9021678383, 0.0410867301, 0.422950774, 0.0211955488, 0.8096830852,
  0.9106092143, 0.888359814, 0.375747412, 0.0681978897, 0.7466816537,
  0.4712936091, 0.120154961, 0.2408971242, 0.7367722704, 0.8220452147,
  0.3240947069, 0.682950617, 0.9079132956, 0.4285258572, 0.146888111,
  0.0876527275, 0.0382878911, 0.0445834764, 0.6848543361, 0.4875632254,
  0.9918960403, 0.117704628, 0.9025166214, 0.3724013027, 0.8358311942,
  0.8561985374, 0.5264625514, 0.424305809, 0.3953265098, 0.008127508,
  0.1773252564, 0.5447534164, 0.0778891353, 0.6220337348, 0.5646875447,
  0.4879517267, 0.1906236359, 0.2546306991, 0.4988814902, 0.6807111634,
  0.3669732618, 0.564151499, 0.5531538269, 0.8426301903, 0.6035581056
};
static const size_t test_bin_packing_values_length =
    sizeof(test_bin_packing_values) / sizeof(double);

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
  puts("test_question_3_8: partial implementation");
  /*
   SortedSet *s = sorted_set_new(compare_int_pointer);
   test_sorted_set(s, test_values, test_values_length);
   object_free((Object *)s);
 
   s = sorted_set_new(compare_int_pointer);
   test_sorted_set(s, test_values_extended, test_values_extended_length);
   object_free((Object *)s);
 	*/
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
    double *predecessor = (double *)dictionary_predecessor((Dictionary *)b, &r);
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
    double *min = (double *)dictionary_min((Dictionary *)b);
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
  assert_equals(bin_packing_worst_fit(test_bin_packing_values,
                                      test_bin_packing_values_length),
                63);
  assert_equals(bin_packing_best_fit(test_bin_packing_values,
                                     test_bin_packing_values_length),
                52);
}

void question_3_11(void) {
  puts("test_question_3_11: partial implementation");
  /*
   RangeContainer *r = array_range_container_new(compare_int_pointer);
   test_range_container(r, test_values, test_values_length);
   object_free((Object *)r);
 
   r = array_range_container_new(compare_int_pointer);
   test_range_container(r, test_values_extended, test_values_extended_length);
   object_free((Object *)r);
 	*/
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
  puts("test_question_3_21");
  BinaryTree *a = binary_tree_new(compare_int_pointer);
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < test_values_length - 1; i++) {
    container_insert((Container *)a, INT_TO_POINTER(test_values[i]));
    container_insert((Container *)b, INT_TO_POINTER(test_values[i]));
  }
  assert_true(binary_tree_compare(a, b));

  container_insert((Container *)a, INT_TO_POINTER(test_values[i]));
  assert_false(binary_tree_compare(a, b));

  object_free((Object *)a);
  object_free((Object *)b);
}

static void linked_stack_visitor(void *p, void *x) {
  stack_push((Stack *)p, x);
}

void question_3_22(void) {
  puts("test_question_3_22");
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < test_values_length; i++)
    container_insert((Container *)b, INT_TO_POINTER(test_values[i]));

  LinkedStack *l = tree_to_linked_stack((Tree *)b);

  assert_false(container_empty((Container *)l));
  int j;
  for (j = (test_values_length - 1); j >= 0; j--)
    assert_equals(POINTER_TO_INT(stack_pop((Stack *)l)),
                  test_values_in_order[j]);
  assert_true(container_empty((Container *)l));
}

void question_3_23(void) {
  puts("test_question_3_23");
  // completed in test_linked_stack
}

static char *reverse_line(const char *line, size_t length) {
  char *reverse = malloc(sizeof(char) * length + 1);
  reverse[length] = '\0';
  size_t i;
  size_t j = 0;
  for (i = j = 0; i <= length; i++) {
    switch (line[i]) {
    case ' ':
      reverse[length - i - 1] = ' ';
    case '\0':
      ; // empty statement
      size_t word_len = i - j;
      memcpy(&reverse[length - i], &line[j], sizeof(char) * word_len);
      j = i + 1;
      break;
    default:
      break;
    }
  }
  return reverse;
}

void question_3_26(void) {
  puts("test_question_3_26");
  static const char *line = "My name is Chris";
  static const char *line_reversed = "Chris is name My";
  char *reverse = reverse_line(line, strlen(line));
  size_t i;
  for (i = 0; i <= strlen(line); i++)
    assert_equals(reverse[i], line_reversed[i]);
}

void question_3_27(void) {
  puts("test_question_3_27");
  Node *head = node_new_leaf(INT_TO_POINTER(0));
  Node *node = head;
  size_t i;
  for (i = 1; i < 6; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  Node *loop = node;
  for (i = 6; i < 9; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  node->n = loop;

  assert_equals(node_loop(head), 6);
}

static int *unordered_product_ignoring_index_with_division(const int *X,
                                                           size_t length) {
  int *M = malloc(sizeof(int) * length);
  size_t i;
  int r = 1;
  for (i = 0; i < length; i++)
    r *= X[i];
  for (i = 0; i < length; i++)
    M[i] = r / X[i];
  return M;
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

static void test_unordered_product_ignoring_index(const int *X, size_t length) {
  int *actual = unordered_product_ignoring_index(X, length);
  size_t i;
  int *expected = unordered_product_ignoring_index_with_division(X, length);
  for (i = 0; i < length; i++)
    assert_equals(actual[i], expected[i]);
  free(actual);
  free(expected);
}

void question_3_28(void) {
  puts("test_question_3_28");
  static int unordered[] = { 6, 5, 3, 1, 7, 6, 2, 3 };
  static size_t unordered_length = sizeof(unordered) / sizeof(int);
  test_unordered_product_ignoring_index(unordered, unordered_length);
}
