#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "compare.h"

#include <stddef.h>

int binary_search(const void *, const void *, size_t, size_t, Compare);
int reduce_int(const int *, size_t, int(*)(int, int), int);

#endif /* ALGORITHM_H */
