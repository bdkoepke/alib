#include "math.h"
#include <stdbool.h>

static bool even(int x) { return x % 2 == 0; }

static int square(int x) { return x * x; }

int power(int a, int n) {
  if (n == 0)
    return 1;
  const int x = power(a, n / 2);
  return even(x) ? square(x) : a * square(x);
}
