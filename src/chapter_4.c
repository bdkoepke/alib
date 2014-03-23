#include "chapter_4.h"
#include "lang/math_extended.h"
#include "lang/sort.h"
#include "lang/type.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
#include "test/test_sort.h"
#include "test/test.h"
#include "util/compare.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void _test_heap(void) {
  puts("test_heap");
  Heap *h = heap_new(compare_int_pointer);
  test_heap_empty(h, test_values, test_values_length);
  object_free((Object *)h);

  h = heap_new(compare_int_pointer);
  test_heap_empty(h, test_values_extended, test_values_extended_length);
  object_free((Object *)h);

  void **mutable_test_values = malloc(sizeof(void *) * test_values_length);
  size_t i;
  for (i = 0; i < test_values_length; i++)
    mutable_test_values[i] = INT_TO_POINTER(test_values[i]);
  h = heap_new_from_array(compare_int_pointer, mutable_test_values,
                          test_values_length);
  test_heap(h, test_values, test_values_length);
  object_free((Object *)h);

  mutable_test_values = malloc(sizeof(void *) * test_values_extended_length);
  for (i = 0; i < test_values_extended_length; i++)
    mutable_test_values[i] = INT_TO_POINTER(test_values_extended[i]);
  h = heap_new_from_array(compare_int_pointer, mutable_test_values,
                          test_values_extended_length);
  test_heap(h, test_values_extended, test_values_extended_length);
  object_free((Object *)h);
}

void test_mergesort(void) {
  puts("test_mergesort");
  test_sort(mergesort);
}

void test_quicksort(void) {
  puts("test_quicksort");
  test_sort(quicksort);
}

void test_binary_search(void) {
  puts("test_binary_search");
  static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t sorted_length = sizeof(sorted) / sizeof(int);

  size_t i;
  for (i = 0; i < sorted_length; i++)
    assert_equals(sorted[binary_search_int(sorted[i], sorted, sorted_length)],
                  sorted[i]);
}

static int right_boundary(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return l;
  size_t m = (l + h) / 2;
  return x < a[m] ? right_boundary(x, a, l, m - 1)
                  : right_boundary(x, a, m + 1, h);
}

static int left_boundary(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return l;
  size_t m = (l + h) / 2;
  return x < a[m] ? left_boundary(x, a, l, m - 1)
                  : left_boundary(x, a, m + 1, h);
}

int count_occurrences(int x, int *s, size_t length) {
  int right = right_boundary(x, s, 0, length - 1);
  int left = left_boundary(x, s, 0, length - 1);
  assert(s[left] == s[right]);
  return s[left] == x ? right - left : 0;
}

void test_count_occurrences(void) {
  puts("test_count_occurrences: partial implementation");
  /* int occurrences[] = { 1, 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };
 	size_t occurrences_length = sizeof(occurrences) / sizeof(int);
 	assert_equals(count_occurrences(3, occurrences, occurrences_length), 5); */
}

static int _one_sided_binary_search(int x, int *a, int i) {
  if (a[i - 1] == x)
    return binary_search_int(x, a, i);
  return _one_sided_binary_search(x, a, i * 2);
}

int one_sided_binary_search(int x, int *a) {
  return _one_sided_binary_search(x, a, 1);
}

void test_one_sided_binary_search(void) {
  puts("test_one_sided_binary_search: partial implementation");
}

void test_sqrt(void) {
  puts("test_sqrt");
  const double p = 0.000001;
  double s = sqrt_int(9, p);
  assert_true(s - 3.0 < p && s - 3.0 > -p);
  s = sqrt_int(6512, p);
  assert_true(s - 80.696964007 < p && s - 80.696964007 > -p);
}

void question_4_1(void) {}
void question_4_2(void) {}
void question_4_3(void) {}
void question_4_4(void) {}
void question_4_5(void) {}
void question_4_6(void) {}
void question_4_7(void) {}
void question_4_8(void) {}
void question_4_9(void) {}
void question_4_10(void) {}
void question_4_11(void) {}
void question_4_12(void) {}

void question_4_14(void) {}
void question_4_15(void) {}
void question_4_16(void) {}
void question_4_17(void) {}
void question_4_18(void) {}
void question_4_19(void) {}
void question_4_20(void) {}

void question_4_22(void) {}
void question_4_23(void) {}
void question_4_24(void) {}
void question_4_25(void) {}
void question_4_26(void) {}
void question_4_27(void) {}

void question_4_31(void) {}

void question_4_33(void) {}
void question_4_34(void) {}
void question_4_35(void) {}

void question_4_44(void) {}
void question_4_45(void) {}
void question_4_46(void) {}
