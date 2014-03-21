#include "sort.h"

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selection_sort(int a[], int length) {
  int i;
  for (i = 0; i < length; i++) {
    int min = i;
    int j;
    for (j = i; j < length; j++)
      if (a[j] < a[min])
        min = j;
    if (min != i)
      swap(&a[i], &a[min]);
  }
}

void insertion_sort(int a[], int length) {
  int i, j;
  for (i = 1; i < length; i++)
    for (j = i; j > 0 && a[j - 1] > a[j]; j--)
      swap(&a[j], &a[j - 1]);
}
