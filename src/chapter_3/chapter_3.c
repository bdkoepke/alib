#include "../test.h"
#include "array.h"
#include "array_container.h"
#include "binary_tree.h"
#include "list.h"
#include "stack.h"
#include "type.h"

#include <stdbool.h>
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
  List *list = list_new();
  size_t i;
  for (i = 0; i < 100; i++) {
    container_insert((Container *)list, INT_TO_POINTER(i));
    assert_equals(
        POINTER_TO_INT(container_search((Container *)list, INT_TO_POINTER(i))),
        i);
  }
  list_reverse(list);
  for (i = 0; i < 100; i++)
    assert_equals(POINTER_TO_INT(list_cadr(list)), i);

  object_free((Object *)list);
}

void question_3_3(void) {
  puts("test_question_3_3");
  Array *array = array_new();
  size_t i;
  for (i = 0; i < 100; i++) {
    container_insert((Container *)array, INT_TO_POINTER(i));
    assert_equals(POINTER_TO_INT(array_get(array, i)), i);
  }
  for (i = 99; i > 0; i--) {
    size_t j = i - 1;
    container_delete((Container *)array, INT_TO_POINTER(j));
    assert_equals(
        POINTER_TO_INT(container_search((Container *)array, INT_TO_POINTER(j))),
        0);
  }

  object_free((Object *)array);
}

void question_3_4(void) {
  puts("test_question_3_4");
  Container *c = array_container_new(100);
  size_t i;
  for (i = 1; i <= 100; i++) {
    container_insert(c, INT_TO_POINTER(i));
    assert_equals(POINTER_TO_INT(container_search(c, INT_TO_POINTER(i))), i);
  }
  for (i = 100; i > 1; i--) {
    container_delete(c, INT_TO_POINTER(i));
    assert_equals(POINTER_TO_INT(container_search(c, INT_TO_POINTER(i))), 0);
  }

  object_free((Object *)c);
}

void question_3_7(void) {
  puts("test_question_3_7");
  int random[] = { 42, 93, 84, 50, 23, 71, 17, 86, 73, 87, 29, 15, 45, 67, 76,
                   27, 78, 38, 51, 57, 26, 89, 12, 19, 10, 7, 94, 75, 21, 55,
                   53, 44, 65, 99, 72, 95, 4, 3, 63, 77, 52, 37, 100, 79, 36,
                   88, 49, 66, 5, 56, 46, 11, 41, 47, 0, 96, 34, 9, 14, 2, 24,
                   58, 74, 64, 33, 28, 35, 60, 82, 1, 25, 39, 48, 6, 90, 20, 43,
                   31, 59, 91, 54, 81, 32, 62, 22, 97, 68, 30, 16, 40, 92, 8,
                   69, 13, 61, 18, 98, 80, 85, 83 };

  BinaryTree *binary_tree = binary_tree_new(compare_int);
  Tree *tree = (Tree *)binary_tree;
  size_t i;
  for (i = 0; i < 100; i++) {
    container_insert((Container *)tree, INT_TO_POINTER(random[i]));
    assert_equals(POINTER_TO_INT(container_search((Container *)tree,
                                                  INT_TO_POINTER(random[i]))),
                  random[i]);
  }
}

void chapter_3(void) {
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
}
