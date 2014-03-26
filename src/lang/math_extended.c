#include "../diag/contract.h"
#include "math_extended.h"

bool even(int x) { return x % 2 == 0; }

bool odd(int x) { return x % 2 == 1; }

int square(int x) { return x * x; }

int power(int a, int n) {
  if (n == 0)
    return 1;
  const int x = power(a, n / 2);
  return even(x) ? square(x) : a * square(x);
}

int min(int a, int b) { return a < b ? a : b; }

int max(int a, int b) { return a > b ? a : b; }

static double _sqrt(unsigned int x, double l, double h, double p) {
  if ((h - l) < p)
    return l;
  double m = (l + h) / 2;
  return x < (m * m) ? _sqrt(x, l, m, p) : _sqrt(x, m, h, p);
}

double sqrt_int(unsigned int x, double p) {
  contract_requires(p < 1 && p > 0);
  return _sqrt(x, 0.0, x, p);
}
