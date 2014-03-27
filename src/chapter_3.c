#include "diag/contract.h"
#include "lang/algorithm.h"
#include "lang/array.h"
#include "lang/math_extended.h"
#include "lang/type.h"
#include "test/test.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
#include "util/array_list.h"
#include "util/array_container.h"
#include "util/binary_tree.h"
#include "util/hashtable.h"
#include "util/linked_queue.h"
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

bool balanced_parenthesis(const char *text, size_t length, int *out_position) {
  contract_requires(text != NULL && length <= strlen(text));

  size_t left_parenthesis = 0;
  size_t i;
  for (i = 0; i < length; i++) {
    switch (text[i]) {
    case '(':
      left_parenthesis++;
      break;
    case ')':
      if (left_parenthesis == 0) {
        if (out_position != NULL)
          *out_position = i;
        return false;
      }
      left_parenthesis--;
      break;
    default:
      continue;
    }
  }
  if (left_parenthesis == 0)
    return true;
  if (out_position != NULL)
    *out_position = i - 1;
  return false;
}

void _test_array_list(void) {
  puts("test_array_list");
  ArrayList *a = array_list_new();
  test_array_list(a, test_values, test_values_length);
  object_free((Object *)a);

  a = array_list_new();
  test_array_list(a, test_values_extended, test_values_extended_length);
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

void test_linked_queue(void) {
  puts("test_linked_queue");
  Queue *q = linked_queue_new();
  test_queue(q, test_values, test_values_length);
  object_free((Object *)q);

  q = linked_queue_new();
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
  int position;
  assert_true(
      balanced_parenthesis("((())())()", strlen("((())())()"), &position));
  assert_false(balanced_parenthesis(")()(", strlen(")()("), &position));
  assert_equals(position, 0);
  assert_false(balanced_parenthesis("()(", strlen("()("), &position));
  assert_equals(position, 2);
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
  ArrayList *a = array_list_new();
  test_container((Container *)a, test_values, test_values_length);
  object_free((Object *)a);

  a = array_list_new();
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

size_t bin_packing(const double *weights, size_t length,
                   bool (*f)(const Dictionary *, double, double *)) {
  bool validate_weight(double weight) { return weight > 0.0 && weight <= 1.0; }
  contract_requires(weights != NULL &&
                    all_double(weights, length, validate_weight));

  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < length; i++)
    container_insert((Container *)b, (void *)&weights[i]);

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    double next;
    if (f((Dictionary *)b, bin, &next)) {
      bin = 0;
      bins++;
    } else {
      bin += next;
      container_delete((Container *)b, &next);
    }
  }
  object_free((Object *)b);
  return bin == 0 ? bins : bins + 1;
}

size_t bin_packing_best_fit(const double *weights, size_t length) {
  bool bin_packing_best_fit_heuristic(const Dictionary * d, double bin,
                                      double * out_next) {
    contract_requires(d != NULL && out_next != NULL);
    *out_next = *(double *)dictionary_predecessor(d, &bin);
    return out_next == NULL;
  }
  return bin_packing(weights, length, bin_packing_best_fit_heuristic);
}

size_t bin_packing_worst_fit(const double *weights, size_t length) {
  bool bin_packing_worst_fit_heuristic(const Dictionary * d, double bin,
                                       double * out_next) {
    contract_requires(d != NULL && out_next != NULL);
    return (*out_next = *(double *)dictionary_min(d)) > (1 - bin);
  }
  return bin_packing(weights, length, bin_packing_worst_fit_heuristic);
}

void question_3_10(void) {
  puts("test_question_3_10");
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

  /*
   assert_equals(bin_packing_worst_fit(test_bin_packing_values,
                                       test_bin_packing_values_length),
                 63);
   assert_equals(bin_packing_best_fit(test_bin_packing_values,
                                      test_bin_packing_values_length),
                 52);
 	*/
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

char *reverse_words_in_line(const char *line, size_t length) {
  contract_requires(line != NULL && length <= strlen(line));

  char *reverse = malloc(sizeof(char) * length + 1);
  reverse[length] = '\0';

  size_t word_start = 0;
  size_t word_end;
  for (word_start = word_end = 0; word_end <= length; word_end++) {
    switch (line[word_end]) {
    case ' ':
      reverse[length - word_end - 1] = ' ';
    case '\0':
      ; // empty statement
      size_t word_len = word_end - word_start;
      memcpy(&reverse[length - word_end], &line[word_start],
             sizeof(char) * word_len);
      word_start = word_end + 1;
      break;
    default:
      break;
    }
  }
  return reverse;
}

void question_3_26(void) {
  puts("test_question_3_26");
  char line[] = "My name is Chris";
  char *reverse = reverse_words_in_line(line, strlen(line));
  assert_memcmp("Chris is name My", reverse);
  free(reverse);
}

void question_3_27(void) {
  puts("test_question_3_27");

  // setup a node loop
  Node *head = node_new_leaf(INT_TO_POINTER(0));
  Node *node = head;
  // six normal nodes
  size_t i;
  for (i = 1; i < 6; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  // save a pointer to the last of the six nodes
  Node *loop = node;
  for (i = 6; i < 9; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  // set number 9's next to 6 creating the loop
  node->n = loop;

  assert_equals(node_loop(head), 6);
}

int *unordered_product_ignoring_index_with_division(const int *X,
                                                    size_t length) {
  contract_requires(X != NULL);

  int *M = malloc(sizeof(int) * length);
  size_t i;
  int r = 1;
  for (i = 0; i < length; i++)
    r *= X[i];
  for (i = 0; i < length; i++)
    M[i] = r / X[i];
  return M;
}

int *unordered_product_ignoring_index(const int *X, size_t length) {
  contract_requires(X != NULL);

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
  int X[] = { 6, 5, 3, 1, 7, 6, 2, 3 };
  size_t length = array_size(X);

  int *actual = unordered_product_ignoring_index(X, length);
  size_t i;
  int *expected = unordered_product_ignoring_index_with_division(X, length);
  for (i = 0; i < length; i++)
    assert_equals(actual[i], expected[i]);
  free(actual);
  free(expected);
}
