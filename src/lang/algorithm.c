#include "../diag/contract.h"
#include "algorithm.h"

static int _binary_search(const void *key, const void *values, size_t low,
                          size_t high, size_t size, Compare c) {
  if (low > high)
    return -1;
  size_t middle = (low + high) / 2;
  const void *p = values + middle * size;
  int r = c(key, p);
  if (r == 0)
    return middle;
  return r < 0 ? _binary_search(key, values, low, middle - 1, size, c)
               : _binary_search(key, values, middle + 1, high, size, c);
}

int binary_search(const void *key, const void *values, size_t length,
                  size_t size, Compare c) {
  return _binary_search(key, contract_requires_non_null(values), 0, length,
                        size, contract_requires_non_null(c));
}

bool all_double(const double *a, size_t length, bool (*p)(double)) {
  contract_requires_non_null(a);
  contract_requires_non_null(p);
  size_t i;
  for (i = 0; i < length; i++)
    if (!p(a[i]))
      return false;
  return true;
}

bool all_int(const int *a, size_t length, bool (*p)(int)) {
  contract_requires_non_null(a);
  contract_requires_non_null(p);
  size_t i;
  for (i = 0; i < length; i++)
    if (!p(a[i]))
      return false;
  return true;
}

int reduce_int(const int *a, size_t length, int (*f)(int a, int b),
               int _default) {
  contract_requires_non_null(a);
  contract_requires_non_null(f);
  int reduce = _default;
  size_t i;
  for (i = 0; i < length; i++)
    reduce = f(reduce, a[i]);
  return reduce;
}

static int _binary_search_int(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return -1;
  size_t m = (l + h) / 2;
  if (a[m] == x)
    return m;
  return x < a[m] ? m == 0 ? -1 : _binary_search_int(x, a, l, m - 1)
                           : _binary_search_int(x, a, m + 1, h);
}

int binary_search_int(int x, const int *a, size_t length) {
  return _binary_search_int(x, a, 0, length - 1);
}
