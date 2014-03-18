#include "algorithm.h"
#include "contract.h"

/*
static int _bsearch_indexof_int(int key, const int *values, Compare c, int _min,
                                int _max) {
  if (_max < _min)
    return -1;
  int i = _min + ((_max - _min) / 2);
  int r = c(values[i], key);
  if (r == 0)
    return i;
  return r < 0 ? _bsearch_indexof_int(key, values, c, _min, i - 1)
               : _bsearch_indexof_int(key, values, c, i + 1, _max);
}
*/

int bsearch_indexof_int(int key, const int *values, size_t length, Compare c) {
  contract_requires(values != NULL && c != NULL);
  contract_requires(false);
  return 0;
  //return _bsearch_indexof_int(key, values, c, 0, length);
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
