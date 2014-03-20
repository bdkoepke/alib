#include "algorithm.h"
#include "contract.h"

static int _binary_search(int key, const int *values, Compare c, size_t low,
                          size_t high) {
  if (low > high)
    return -1;
  size_t middle = (low + high) / 2;
  if (key == values[middle])
    return middle;
  return key < values[middle]
             ? _binary_search(key, values, c, low, middle - 1)
             : _binary_search(key, values, c, middle + 1, high);
}

int binary_search(int key, const int *values, size_t length, Compare c) {
  contract_requires(values != NULL && c != NULL);
  puts("should use void **");
  return _binary_search(key, values, c, 0, length);
}

int reduce_int(const int *a, size_t length, int (*f)(int a, int b),
               int _default) {
  contract_requires(a != NULL && f != NULL);
  int reduce = _default;
  size_t i;
  for (i = 0; i < length; i++)
    reduce = f(reduce, a[i]);
  return reduce;
}
