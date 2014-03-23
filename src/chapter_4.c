#include "chapter_4.h"
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

static int _binary_search_int(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return -1;
  size_t m = (l + h) / 2;
  if (a[m] == x)
    return m;
  return x < a[m] ? _binary_search_int(x, a, l, m - 1)
                  : _binary_search_int(x, a, m + 1, h);
}

int binary_search_int(int x, const int *a, size_t length) {
  return _binary_search_int(x, a, 0, length - 1);
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

void test_count_occurrences(void) {}
