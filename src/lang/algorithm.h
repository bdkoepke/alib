#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../util/compare.h"

#include <stddef.h>

int reduce_int(const int *, size_t, int(*)(int, int), int);
int binary_search(const void *, const void *, size_t, size_t, Compare);

#endif /* ALGORITHM_H */
