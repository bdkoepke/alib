#include "chapter_2.h"
#include "lang/math_extended.h"
#include "lang/sort.h"
#include "lang/string.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int expected[] = { 1, 2, 3, 4, 5, 6, 7, 9 };
const size_t expected_size = sizeof(expected);
const size_t expected_length = sizeof(expected) / sizeof(int);
int *unsorted;

static void setup(void) {
  int _unsorted[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
  if (unsorted)
    free(unsorted);
  unsorted = malloc(expected_size);
  memcpy(unsorted, _unsorted, expected_size);
}

static void show_array(int a[], size_t length) {
  if (length == 0)
    return;
  printf("{ ");
  int i;
  for (i = 0; i < (length - 1); i++)
    printf("%d, ", a[i]);
  printf("%d }\n", a[length - 1]);
}

void test_selection_sort(void) {
  printf("test_selection_sort\n");
  setup();
  selection_sort(unsorted, expected_length);
  assert(memcmp(expected, unsorted, expected_size) == 0);
}

void test_insertion_sort(void) {
  printf("test_insertion_sort\n");
  setup();
  insertion_sort(unsorted, expected_length);
  assert(memcmp(expected, unsorted, expected_size) == 0);
}

void test_find_match(void) {
  printf("test_find_match\n");
  assert(find_match("pattern", "this is a pattern") == 10);
}

void test_power(void) {
  printf("test_power\n");
  assert(power(2, 16) == 65536);
}
