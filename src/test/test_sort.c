#include "test.h"
#include "test_sort.h"

#include <assert.h>
#include <string.h>

void test_sort(sort s) {
  static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  int _unsorted[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
  int *unsorted = malloc(sizeof(_unsorted));
  memcpy(unsorted, _unsorted, sizeof(_unsorted));
  s(unsorted, sizeof(_unsorted) / sizeof(int));
  assert_equals(memcmp(unsorted, sorted, sizeof(_unsorted) / sizeof(int)), 0);
}
