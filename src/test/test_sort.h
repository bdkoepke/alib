#ifndef TEST_SORT_H
#define TEST_SORT_H

#include <stddef.h>

typedef void (*Sort)(int a[], size_t);

void test_sort(Sort);

#endif /* TEST_SORT_H */
