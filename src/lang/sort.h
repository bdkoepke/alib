#ifndef SORT_H
#define SORT_H

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
int *buckets_new(int a[], int length, int max);

/** Various sort implementations */
void selectionsort(int a[], int length);
void insertionsort(int a[], int length);
void mergesort(int a[], int length);
void quicksort(int a[], int length);
void bucketsort(int a[], int n, int max);

#endif /* SORT_H */
