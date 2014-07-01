#ifndef MATH_EXTENDED_H
#define MATH_EXTENDED_H

#include <stdbool.h>
#include <stddef.h>

bool even(int);
bool odd(int);
int max(int, int);
int min(int, int);
int power(int a, int n);
int square(int);
double sqrt_int(unsigned int, double);

/**
 * Safe multiplication with default value in case of failure.
 */
size_t checked_product(size_t multiplicand, size_t multiplier, size_t _default);

#endif /* MATH_EXTENDED_H */
