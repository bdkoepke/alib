#include "chapter_2.h"
#include "lang/math_extended.h"
#include "lang/sort.h"
#include "lang/string.h"
#include "test/test.h"
#include "test/test_sort.h"

#include <stdio.h>
#include <string.h>

void test_selectionsort(void) {
  puts("test_selectionsort");
  test_sort(selectionsort);
}

void test_insertionsort(void) {
  puts("test_insertionsort");
  test_sort(insertionsort);
}

void test_find_match(void) {
  puts("test_find_match");
  const char pattern[] = "pattern";
  const char text[] = "this is a pattern";
  assert_equals(
      find_match(pattern, text, (int)strlen(pattern), (int)strlen(text)), 10);
}

void test_power(void) {
  puts("test_power");
  assert_equals(power(2, 16), 65536);
}
