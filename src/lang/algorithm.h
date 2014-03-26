#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../util/compare.h"

#include <stdbool.h>
#include <stddef.h>

// TODO: use c11 generics

bool all_double(const double *, size_t, bool (*)(double));
bool all_int(const int *, size_t, bool(*)(int));
int reduce_int(const int *, size_t, int(*)(int, int), int);

int binary_search(const void *, const void *, size_t, size_t, Compare);
int binary_search_int(int, const int *, size_t);

#endif /* ALGORITHM_H */
