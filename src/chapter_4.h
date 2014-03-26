#ifndef CHAPTER_4_H
#define CHAPTER_4_H

#include <stddef.h>

int count_occurrences(int x, int *s, size_t length);
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

/** Basic collection tests. */
void _test_heap(void);
void test_mergesort(void);
void test_quicksort(void);
void test_count_occurrences(void);
void test_sqrt(void);
void test_max_min(void);
void test_bucketsort(void);

void question_4_1(void);
void question_4_2(void);
void question_4_3(void);
void question_4_4(void);
void question_4_5(void);
void question_4_6(void);
void question_4_7(void);
void question_4_8(void);
void question_4_9(void);
void question_4_10(void);
void question_4_11(void);
void question_4_12(void);

void question_4_14(void);
void question_4_15(void);
void question_4_16(void);
void question_4_17(void);
void question_4_18(void);
void question_4_19(void);
void question_4_20(void);

void question_4_22(void);
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
