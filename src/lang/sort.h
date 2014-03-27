#ifndef SORT_H
#define SORT_H

#include <stddef.h>

/**
 * Swaps the two values.
 *
 * @param a the first parameter.
 * @param b the second parameter.
 */
void swap(int *a, int *b);

/**
 * Creates a new array containing the bucket count
 * from bucketsort.
 *
 * @param a the array to use to initialize the buckets.
 * @param length the length of the array.
 * @param max the maximum value of the elements in the array.
 * @return an array with the bucket count from bucketsort.
 */
int *buckets_new(int a[], size_t length, int max);

/** Various sort implementations */
void selectionsort(int a[], size_t length);
void insertionsort(int a[], size_t length);
void mergesort(int a[], size_t length);
void quicksort(int a[], size_t length);
void bucketsort(int a[], size_t length, int max);

/**
 * Quickly selects the kth ordered element from the list.
 *
 * @param a the array to get the kth element from.
 * @param length the length of the array.
 * @param k the index of the ordered element to obtain.
 * @return the element at the specified ordered position
 * 	in the array.
 */
int quickselect(int a[], size_t length, size_t k);

#endif /* SORT_H */
