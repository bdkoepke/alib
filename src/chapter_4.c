#include "chapter_4.h"
#include "lang/sort.h"
#include "lang/type.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
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
	int unsorted[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
	static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	mergesort(unsorted, sizeof(unsorted) / sizeof(int));
	assert (memcmp(unsorted, sorted, sizeof(unsorted) / sizeof(int)) == 0);
}

void test_quicksort(void) {
	puts("test_quicksort");
	int unsorted[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
	static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	quicksort(unsorted, sizeof(unsorted) / sizeof(int));
	assert (memcmp(unsorted, sorted, sizeof(unsorted) / sizeof(int)) == 0);
}
