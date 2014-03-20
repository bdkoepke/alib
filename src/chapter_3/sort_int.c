#include "sort_int.h"

#include <stdlib.h>
#include <string.h>

static int compare_int(const void *a, const void *b) {
  int _a = *((const int *)a);
  int _b = *((const int *)b);
  return _a - _b;
}

int *sort_int(const int *values, size_t length) {
  int *sorted = malloc(sizeof(int) * length);
  memcpy(sorted, values, sizeof(int) * length);
  qsort(sorted, length, sizeof(int), compare_int);
  return sorted;
}
