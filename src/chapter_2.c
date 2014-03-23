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

static int *unsorted_new(void) {
  static const int _unsorted[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
  int *unsorted = malloc(expected_length * sizeof(int));
  memcpy(unsorted, _unsorted, expected_length * sizeof(int));
	return unsorted;
}

static void show_array(int a[], size_t length) {
  if (length == 0)
    return;
	puts("{ ");
  int i;
  for (i = 0; i < (length - 1); i++)
    printf("%d, ", a[i]);
  printf("%d }\n", a[length - 1]);
}

void test_selectionsort(void) {
	puts("test_selectionsort");
	int *unsorted = unsorted_new();
  selectionsort(unsorted, expected_length);
  assert(memcmp(expected, unsorted, expected_size) == 0);
	free(unsorted);
}

void test_insertionsort(void) {
	puts("test_insertionsort");
	int *unsorted = unsorted_new();
  insertionsort(unsorted, expected_length);
  assert(memcmp(expected, unsorted, expected_size) == 0);
	free(unsorted);
}

void test_find_match(void) {
	puts("test_find_match");
  assert(find_match("pattern", "this is a pattern") == 10);
}

void test_power(void) {
	puts("test_power");
  assert(power(2, 16) == 65536);
}
