#ifndef CHAPTER_3_H
#define CHAPTER_3_H

#include "util/dictionary.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * Determines whether the specified string has balanced parenthesis.
 *
 * @param s the string to verify the paranthesis of.
 * @param length the length of the string.
 * @param out_position the position in the string of the first unbalanced
 * 	string.
 * @return true if the string is balanced, false otherwise.
 */
bool balanced_parenthesis(const char *text, size_t length, int *out_position);

/**
 * Heuristic to determine which bin should be selected next.
 *
 * @param d the dictionary used to select the next bin.
 * @param bin the size of the current bin, will be >= 0 && < 1.
 * @param out_next the next bin.
 * @return true if there is a weight that will fit in the current bin,
 * 	false otherwise.
 */
typedef bool (*bin_packing_heuristic)(const Dictionary *b, double bin, double *out_next);

/**
 * Bin packing problem.
 *
 * @param weights a set of weights.
 * @param length the number of weights.
 * @param heuristic the heuristic to use to determine the next bin from the
 * 	available bins.
 * @return the number of required bins as determined by the specified
 * 	heuristic.
 */
size_t bin_packing(const double *weights, size_t length, bin_packing_heuristic heuristic);

/**
 * Bin packing problem that selects the largest remaining weight that will fit
 * in the bin.
 */
size_t bin_packing_best_fit(const double *weights, size_t length);

/**
 * Bin packing problem that selects the smallest remaining weight that will fit
 * in the bin.
 */
size_t bin_packing_worst_fit(const double *weights, size_t length);

/**
 * Returns a copy of the specified line with the words in the reverse order.
 * 
 * Example: reverse_words_in_line("This line is a line") = "line a is line This"
 *
 * @param line the line to copy the reverse of.
 * @param length the length of the line.
 * @return a copy of the specified line with the words reversed, null terminated.
 */
char *reverse_words_in_line(const char *line, size_t length);

/**
 * Finds the array $M$ containing $n$ elements where $M_i$ is the product of all
 * integers in $X$ except for $X_i$ using division.
 *
 * @param X the set of elements.
 * @param length the number of elements in $X$.
 * @return the array $M$
 */
int *unordered_product_ignoring_index_with_division(const int *X, size_t length);

/**
 * Finds the array $M$ containing $n$ elements where $M_i$ is the product of all
 * integers in $X$ except for $X_i$ without using division.
 *
 * @param X the set of elements.
 * @param length the number of elements in $X$.
 * @return the array $M$
 */
int *unordered_product_ignoring_index(const int *X, size_t length);

/** Basic collection tests. */
void _test_array_list(void);
void _test_linked_stack(void);
void test_linked_queue(void);
void test_binary_tree(void);
void test_red_black_tree(void);
void test_hashtable(void);

void question_3_1(void);
void question_3_2(void);
void question_3_3(void);
void question_3_4(void);
void question_3_7(void);
void question_3_8(void);
void question_3_9(void);
void question_3_10(void);
void question_3_11(void);
void question_3_13(void);
void question_3_14(void);
void question_3_15(void);
void question_3_20(void);
void question_3_21(void);
void question_3_22(void);
void question_3_23(void);
void question_3_26(void);
void question_3_27(void);
void question_3_28(void);

#endif /* CHAPTER_3_H */
