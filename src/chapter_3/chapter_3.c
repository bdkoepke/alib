#include "../test.h"
#include "array.h"
#include "array_container.h"
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
}

void question_3_7(void) { puts("test_question_3_7"); }

void chapter_3(void) {
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
}
