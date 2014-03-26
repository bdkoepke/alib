#ifndef SORT_H
#define SORT_H

/**
 * Swaps the two values.
 *
 * @param a the first parameter.
 * @param b the second parameter.
 */
void swap(int *a, int *b);

/** Various sort implementations */
void selectionsort(int a[], int length);
void insertionsort(int a[], int length);
void mergesort(int a[], int length);
void quicksort(int a[], int length);
void bucketsort(int a[], int n, int max);

#endif /* SORT_H */
