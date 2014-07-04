#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_puts(const int a[], int length) {
  if (length == 0)
    return;
  printf("{ ");
  int i;
  for (i = 0; i < (length - 1); i++)
    printf("%d, ", a[i]);
  printf("%d }\n", a[length - 1]);
}

int *array_copy(const int a[], int length) {
  int *copy = malloc(length * sizeof(int));
  memcpy(copy, a, length * sizeof(int));
  return copy;
}
