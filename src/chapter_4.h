#ifndef CHAPTER_4_H
#define CHAPTER_4_H

#include <stddef.h>

/**
 * Counts the number of occurrences of the element x
 * in the specified array.
 *
 * @param a the array to search.
 * @param length the length of the array.
 * @param x the element to search for.
 * @return the number of occurrences of the element.
 */
size_t count_occurrences(int a[], size_t length, int x);

/**
 * Computes max and min in $n + ceiling(\frac{n}{2})$ comparisons.
 *
 * @param a the array to find the max and min of. The array itself is used as
 * 	scratch space for the computation.
 * @param length the length of the array.
 * @param out_max the result maximum value.
 * @param out_min the result minimum value.
 */
void max_min(int *a, size_t length, int *out_max, int *out_min);

/** Basic lang tests. */
void _test_heap(void);
void _test_vector(void);
void test_binary_search(void);
void test_binary_sort(void);
void test_bucketsort(void);
void test_count_occurrences(void);
void test_max_min(void);
void test_mergesort(void);
void test_quicksort(void);
void test_sqrt(void);

void question_4_1(void);
void question_4_2(void);
void question_4_3(void);
void question_4_4(void);
void question_4_5(void);
void question_4_6(void);

void question_4_8(void);
void question_4_9(void);
void question_4_10(void);
void question_4_11(void);
void question_4_12(void);

void question_4_14(void);
void question_4_15(void);
void question_4_16(void);

void question_4_18(void);
void question_4_20(void);

void question_4_23(void);
void question_4_24(void);
void question_4_25(void);
void question_4_26(void);
void question_4_27(void);

void question_4_31(void);

void question_4_33(void);
void question_4_34(void);
void question_4_35(void);

void question_4_44(void);
void question_4_45(void);
void question_4_46(void);

#endif /* CHAPTER_4_H */
