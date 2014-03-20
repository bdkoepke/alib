#include "../math.h"
#include "../test.h"
#include "algorithm.h"
#include "array.h"
#include "array_container.h"
#include "binary_tree.h"
#include "chapter_3_values.h"
#include "hashtable.h"
#include "sort_int.h"
#include "sparse_array.h"
#include "stack.h"
#include "test_container.h"
#include "type.h"

#include <assert.h>
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

void _test_stack(void) {
  puts("test_stack");
  Stack *s = stack_new();
  test_stack(s, test_values, test_values_length);
  object_free((Object *)s);

  s = stack_new();
  test_stack(s, test_values_extended, test_values_extended_length);
  object_free((Object *)s);
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
  static const int pre_order[] = { 15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18, 23 };
  static const int in_order[] = { 3, 5, 6, 7, 10, 12, 13, 15, 16, 18, 20, 23 };
  static const int post_order[] = { 3, 7, 6, 10, 13, 12, 5, 18, 23, 20, 16,
                                    15 };
  static const int level_order[] = { 15, 5, 16, 3, 12, 20, 10, 13, 18, 23, 6,
                                     7 };

  BinaryTree *b = binary_tree_new(compare_int_pointer);
  test_tree((Tree *)b, test_values, test_values_length, pre_order, in_order,
            post_order, level_order);
  object_free((Object *)b);

  b = binary_tree_new(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
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
  Stack *s = stack_new();
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
  test_dictionary((Dictionary *)b, test_values, test_values_length);
  object_free((Object *)b);

  b = binary_tree_new(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void question_3_8(void) {
  puts("test_question_3_8");
  SortedSet *s = sorted_set_new(compare_int_pointer);
  test_sorted_set(s, test_values, test_values_length);
  //object_free((Object *)s);

  s = sorted_set_new(compare_int_pointer);
  test_sorted_set(s, test_values_extended, test_values_extended_length);
  //object_free((Object *)s);
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

static size_t bin_packing_best_fit(double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, INT_TO_POINTER(w[i]));

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    void *predecessor =
        dictionary_predecessor((Dictionary *)b, INT_TO_POINTER(1 - bin));
    if (predecessor == NULL) {
      bins++;
      bin = 0;
    } else {
      container_delete((Container *)b, predecessor);
      bin -= (double)(long)(predecessor);
    }
  }
  object_free((Object *)b);
  return bins;
}

static size_t bin_packing_worst_fit(double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, INT_TO_POINTER(w[i]));

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    double min = (double)(long) dictionary_min((Dictionary *)b);
    if ((1 - bin) < min) {
      bins++;
      bin = 0;
    } else {
      bin += min;
      container_delete((Container *)b, INT_TO_POINTER(min));
    }
  }
  object_free((Object *)b);
  return bins;
}

void question_3_10(void) {
  puts("test_question_3_10: not implemented");
  static double objects[] = {
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
  static const size_t objects_length = 100;
  assert(sizeof(double) == sizeof(void *));

  //printf("%d\n", bin_packing_worst_fit(objects, objects_length));
}

void question_3_11(void) { puts("test_question_3_11: not implemented"); }

void question_3_14(void) { puts("test_question_3_14: not implemented"); }

void question_3_15(void) {
  puts("test_question_3_15");
  Array *a =
      sparse_array_new(reduce_int(test_values, test_values_length, max, 0) + 1,
                       test_values_length);
  test_array(a, test_values, test_values_length);
  object_free((Object *)a);

  a = sparse_array_new(
      reduce_int(test_values_extended_positive,
                 test_values_extended_positive_length, max, 0) + 1,
      test_values_extended_positive_length);
  test_array(a, test_values_extended_positive,
             test_values_extended_positive_length);
  object_free((Object *)a);
}

void chapter_3(void) {
  _test_array();
  _test_stack();
  _test_queue();
  test_binary_tree();
  test_hashtable();
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
  question_3_8();
  question_3_9();
  question_3_10();
  question_3_11();
  question_3_14();
  question_3_15();
}
