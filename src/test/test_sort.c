#include "../lang/array.h"
#include "test.h"
#include "test_sort.h"

#include <stdlib.h>

void test_sort(Sort s) {
  static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  int _unsorted[] = { 3, 7, 4, 9, 8, 5, 2, 6, 1 };
  int *unsorted = array_copy(_unsorted, array_size(_unsorted));
  s(unsorted, sizeof(_unsorted) / sizeof(int));
  assert_memcmp(sorted, unsorted);
  free(unsorted);
}
