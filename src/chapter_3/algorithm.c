#include "algorithm.h"

int max(int a, int b) { return a > b ? a : b; }

int reduce(const int *a, size_t length, int (*f)(int a, int b),
                  int _default) {
  int reduce = _default;
  size_t i;
  for (i = 0; i < length; i++)
    reduce = f(reduce, a[i]);
  return reduce;
}
