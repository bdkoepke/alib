#include "array.h"

#include <stdio.h>

void array_puts(const int a[], int length) {
  if (length == 0)
    return;
  puts("{ ");
  int i;
  for (i = 0; i < (length - 1); i++)
    printf("%d, ", a[i]);
  printf("%d }\n", a[length - 1]);
}
