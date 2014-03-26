#include "chapter_4.h"
#include "diag/contract.h"
#include "lang/array.h"
#include "lang/math_extended.h"
#include "lang/sort.h"
#include "lang/tuple.h"
#include "lang/type.h"
#include "test/test.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
#include "test/test_sort.h"
#include "util/compare.h"
#include "util/linked_queue.h"
#include "util/linked_stack.h"
#include "util/stack.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void _test_heap(void) {
  puts("test_heap");
  Heap *h = heap_new(compare_int_pointer);
  test_heap_empty(h, test_values, test_values_length);
  object_free((Object *)h);

  h = heap_new(compare_int_pointer);
  test_heap_empty(h, test_values_extended, test_values_extended_length);
  object_free((Object *)h);

  void **mutable_test_values = malloc(sizeof(void *) * test_values_length);
  size_t i;
  for (i = 0; i < test_values_length; i++)
    mutable_test_values[i] = INT_TO_POINTER(test_values[i]);
  h = heap_new_from_array(compare_int_pointer, mutable_test_values,
                          test_values_length);
  test_heap(h, test_values, test_values_length);
  object_free((Object *)h);

  mutable_test_values = malloc(sizeof(void *) * test_values_extended_length);
  for (i = 0; i < test_values_extended_length; i++)
    mutable_test_values[i] = INT_TO_POINTER(test_values_extended[i]);
  h = heap_new_from_array(compare_int_pointer, mutable_test_values,
                          test_values_extended_length);
  test_heap(h, test_values_extended, test_values_extended_length);
  object_free((Object *)h);
}

void test_mergesort(void) {
  puts("test_mergesort");
  test_sort(mergesort);
}

void test_quicksort(void) {
  puts("test_quicksort");
  test_sort(quicksort);
}

void test_binary_search(void) {
  puts("test_binary_search");
  static const int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t sorted_length = sizeof(sorted) / sizeof(int);

  size_t i;
  for (i = 0; i < sorted_length; i++)
    assert_equals(sorted[binary_search_int(sorted[i], sorted, sorted_length)],
                  sorted[i]);
}

static int right_boundary(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return l;
  size_t m = (l + h) / 2;
  return x < a[m] ? right_boundary(x, a, l, m - 1)
                  : right_boundary(x, a, m + 1, h);
}

static int left_boundary(int x, const int *a, size_t l, size_t h) {
  if (l > h)
    return l;
  size_t m = (l + h) / 2;
  return x < a[m] ? left_boundary(x, a, l, m - 1)
                  : left_boundary(x, a, m + 1, h);
}

int count_occurrences(int x, int *s, size_t length) {
  int right = right_boundary(x, s, 0, length - 1);
  int left = left_boundary(x, s, 0, length - 1);
  assert(s[left] == s[right]);
  return s[left] == x ? right - left : 0;
}

void test_count_occurrences(void) {
  puts("test_count_occurrences: partial implementation");
  /* int occurrences[] = { 1, 2, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9 };
 	size_t occurrences_length = sizeof(occurrences) / sizeof(int);
 	assert_equals(count_occurrences(3, occurrences, occurrences_length), 5); */
}

static int _one_sided_binary_search(int x, int *a, int i) {
  if (a[i - 1] == x)
    return binary_search_int(x, a, i);
  return _one_sided_binary_search(x, a, i * 2);
}

int one_sided_binary_search(int x, int *a) {
  return _one_sided_binary_search(x, a, 1);
}

void test_one_sided_binary_search(void) {
  puts("test_one_sided_binary_search: partial implementation");
}

void test_sqrt(void) {
  puts("test_sqrt");
  const double p = 0.000001;
  double s = sqrt_int(9, p);
  assert_true(s - 3.0 < p && s - 3.0 > -p);
  s = sqrt_int(6512, p);
  assert_true(s - 80.696964007 < p && s - 80.696964007 > -p);
}

void partition_players(int *a, size_t length, int *team_a, int *team_b) {
  contract_requires(even(length));
  size_t half = length / 2;

  quicksort(a, length);

  size_t i;
  for (i = 0; i < half; i++) {
    team_a[i] = a[i];
    team_b[i] = a[i + half];
  }
}

void question_4_1(void) {
  puts("question_4_1");
  int players[] = { 3, 7, 4, 9, 5, 2, 6, 1 };
  size_t players_length = array_size(players);
  size_t team_size = players_length / 2;
  int team_a[team_size];
  int team_b[team_size];
  partition_players(players, players_length, team_a, team_b);
  int expected_team_a[] = { 1, 2, 3, 4 };
  int expected_team_b[] = { 5, 6, 7, 8 };
  assert_equals(memcmp(team_a, expected_team_a, team_size), 0);
  assert_equals(memcmp(team_b, expected_team_b, team_size), 0);
}

void max_min(int *a, size_t len, int *max, int *min) {
  contract_requires(len > 0);
  int _max = INT_MIN;
  int _min = INT_MAX;

  size_t len_half = (len / 2);
  size_t middle = even(len) ? len_half : len_half + 1;
  size_t i;
  for (i = 0; i < len_half; i++)
    if (a[i] > a[i + middle])
      swap(&a[i], &a[i + middle]);
  for (i = 0; i <= middle; i++)
    if (a[i] < _min)
      _min = a[i];
  for (i = len_half; i < len; i++)
    if (a[i] > _max)
      _max = a[i];
  *max = _max;
  *min = _min;
}

void test_max_min(void) {
  puts("test_max_min");
  int S[] = { 6, 13, 19, 3, 8 };
  int max, min;
  max_min(S, array_size(S), &max, &min);
  assert_equals(min, 3);
  assert_equals(max, 19);
  int _S[] = { 6, 13, 19, 3, 8, 20 };
  max_min(_S, array_size(_S), &max, &min);
  assert_equals(min, 3);
  assert_equals(max, 20);
}

void question_4_2(void) {
  puts("question_4_2");
  int S[] = { 6, 13, 19, 3, 8 };
  int max, min;
  max_min(S, array_size(S), &max, &min);
  assert_equals(max - min, 16);

  int sorted[] = { 3, 6, 8, 13, 19 };
  assert_equals(sorted[array_size(sorted) - 1] - sorted[0], 16);

  int s, e, d;
  s = 0;
  e = INT_MAX;
  d = INT_MAX;
  size_t i;
  for (i = 0; i < (array_size(sorted) - 1); i++)
    if (sorted[i + 1] - sorted[i] < d) {
      s = i;
      e = i + 1;
      d = sorted[e] - sorted[s];
    }
  assert_equals(d, 2);
}

void min_partition_pairs(int *a, int n, Tuple **t) {
  contract_requires(even(n));
  quicksort(a, n);
  size_t i;
  for (i = 0; i < (n / 2); i++)
    t[i] = tuple_new(&a[i], &a[n - i - 1]);
}

void question_4_3(void) {
  puts("question_4_3");
  int numbers[] = { 1, 3, 5, 9 };
  int numbers_length = array_size(numbers);
  Tuple *pairs[numbers_length / 2];
  min_partition_pairs(numbers, numbers_length, pairs);
  assert_equals(*(int *)pairs[0]->first, 1);
  assert_equals(*(int *)pairs[0]->second, 9);
  assert_equals(*(int *)pairs[1]->first, 3);
  assert_equals(*(int *)pairs[1]->second, 5);
}

typedef enum {
  red = 0,
  blue = 1,
  yellow = 2
} Color;

const char *color_to_string(Color c) {
  switch (c) {
  case red:
    return "red";
  case blue:
    return "blue";
  case yellow:
    return "yellow";
  }
}

void question_4_4(void) {
  puts("question_4_4");
  typedef struct {
    int i;
    Color c;
  } ColorPair;

  ColorPair pairs[] = { { 1, blue }, { 3, red }, { 4, blue }, { 6, yellow },
                        { 9, red } };
  size_t pairs_length = array_size(pairs);
  Queue *buckets[] = { linked_queue_new(), linked_queue_new(),
                       linked_queue_new() };

  size_t i;
  for (i = 0; i < pairs_length; i++)
    queue_enqueue(buckets[pairs[i].c], &pairs[i]);

  ColorPair sorted_pairs[pairs_length];
  size_t j = 0;
  for (i = 0; i < array_size(buckets); i++)
    while (!container_empty((Container *)buckets[i]))
      sorted_pairs[j++] = *(ColorPair *)queue_dequeue(buckets[i]);

  ColorPair expected[] = { { 3, red }, { 9, red }, { 1, blue }, { 4, blue },
                           { 6, yellow } };

  for (i = 0; i < pairs_length; i++) {
    assert_equals(sorted_pairs[i].i, expected[i].i);
    assert_equals(sorted_pairs[i].c, expected[i].c);
  }
}

static void _bucketsort(int a[], int n) {
  bucketsort(a, n, reduce_int(a, n, max, 0));
}

void test_bucketsort(void) {
  puts("test_bucketsort");
  test_sort(_bucketsort);
}

size_t find_mode(int a[], size_t len) {
  int *b = buckets_new(a, len, reduce_int(a, len, max, 0));

  int bucket_value = 0;
  size_t i, largest_bucket;
  for (i = largest_bucket = 0; i < len; i++)
    if (b[i] > largest_bucket) {
      largest_bucket = b[i];
      bucket_value = i;
    }
  free(b);
  return bucket_value;
}

void question_4_5(void) {
  puts("question_4_5");
  int numbers[] = { 4, 6, 2, 4, 3, 1 };
  size_t numbers_length = array_size(numbers);
  assert_equals(find_mode(numbers, numbers_length), 4);
}

bool sum_pair_equals_x(int S_1[], int S_2[], size_t len, int x) {
  // TODO: ignores integer overflow, should also be able to early exit...
  contract_requires(S_1 != NULL && S_2 != NULL);

  quicksort(S_1, len);
  quicksort(S_2, len);
  size_t i;
  for (i = 0; i < len; i++)
    if (binary_search_int(x - S_1[i], S_2, len) != -1)
      return true;
  return false;
}

void question_4_6(void) {
  puts("question_4_6");
  int S_1[] = { 1, 2, 3, 4, 5, 6 };
  int S_2[] = { 7, 8, 9, 10, 11, 12 };

  assert_true(sum_pair_equals_x(S_1, S_2, array_size(S_1), 18));
  assert_false(sum_pair_equals_x(S_1, S_2, array_size(S_1), 19));
  assert_false(sum_pair_equals_x(S_1, S_2, array_size(S_1), 7));
  assert_true(sum_pair_equals_x(S_1, S_2, array_size(S_1), 8));
}

void sorted_set_union(const int A[], const int B[], size_t A_len, size_t B_len,
                      int **U_p, size_t *U_len) {
  // TODO: add contracts...
  int *U = malloc(sizeof(int) * (A_len + B_len));
  *U_p = U;

  size_t i, j, k;
  i = j = k = 0;
  while (i < A_len && j < B_len)
    if (A[i] == B[j]) {
      j++;
      U[k++] = A[i++];
    } else
      U[k++] = A[i] < B[j] ? A[i++] : B[j++];

  while (i < A_len)
    U[k++] = A[i++];
  while (j < B_len)
    U[k++] = B[j++];

  U = realloc(U, k * sizeof(int));
  *U_len = k;
}

void set_union(int A[], int B[], size_t A_len, size_t B_len, int **U_p,
               size_t *U_len, Sort sort) {
  sort(A, A_len);
  sort(B, B_len);
  sorted_set_union(A, B, A_len, B_len, U_p, U_len);
}

void question_4_8(void) {
  puts("question_4_8");

  int A[] = { 139, 127, 218, 117, 1, 76, 186, 190, 165, 53, 123, 58, 189, 42,
              236, 72, 7, 67, 128, 23, 244, 206, 65, 203, 59, 137, 144, 175, 61,
              60, 66, 200, 16, 29, 208, 95, 187, 211, 131, 28, 135, 146, 107,
              162, 0, 82, 166, 223, 193, 41, 90, 181, 79, 251, 18, 243, 216,
              122, 118, 36, 12, 188, 195, 8, 113, 56, 147, 149, 22, 98, 93, 210,
              133, 84, 246, 220, 73, 227, 9, 2, 192, 183, 152, 157, 71, 39, 198,
              138, 212, 234, 142, 47, 25, 202, 215, 37, 125, 50, 30, 109 };
  int B[] = { 79, 64, 199, 44, 194, 192, 250, 95, 149, 1, 227, 115, 223, 226,
              159, 243, 113, 127, 253, 165, 48, 75, 231, 164, 134, 179, 193,
              205, 236, 160, 19, 3, 126, 73, 210, 116, 169, 18, 37, 16, 94, 162,
              97, 86, 221, 122, 38, 208, 136, 46, 233, 5, 17, 244, 55, 84, 137,
              186, 142, 175, 28, 99, 202, 191, 156, 112, 222, 220, 218, 76, 171,
              245, 139, 242, 209 };
  int S[] = { 0, 1, 2, 3, 5, 7, 8, 9, 12, 16, 17, 18, 19, 22, 23, 25, 28, 29,
              30, 36, 37, 38, 39, 41, 42, 44, 46, 47, 48, 50, 53, 55, 56, 58,
              59, 60, 61, 64, 65, 66, 67, 71, 72, 73, 75, 76, 79, 82, 84, 86,
              90, 93, 94, 95, 97, 98, 99, 107, 109, 112, 113, 115, 116, 117,
              118, 122, 123, 125, 126, 127, 128, 131, 133, 134, 135, 136, 137,
              138, 139, 142, 144, 146, 147, 149, 152, 156, 157, 159, 160, 162,
              164, 165, 166, 169, 171, 175, 179, 181, 183, 186, 187, 188, 189,
              190, 191, 192, 193, 194, 195, 198, 199, 200, 202, 203, 205, 206,
              208, 209, 210, 211, 212, 215, 216, 218, 220, 221, 222, 223, 226,
              227, 231, 233, 234, 236, 242, 243, 244, 245, 246, 250, 251, 253 };

  int *U;
  size_t length;
  set_union(A, B, array_size(A), array_size(B), &U, &length, quicksort);
  assert_memcmp(S, U);
  free(U);

  sorted_set_union(A, B, array_size(A), array_size(B), &U, &length);
  assert_memcmp(S, U);
  free(U);
}

void question_4_9(void) {}
void question_4_10(void) {}
void question_4_11(void) {}
void question_4_12(void) {}
void question_4_14(void) {}
void question_4_15(void) {}
void question_4_16(void) {}
void question_4_17(void) {}
void question_4_18(void) {}
void question_4_19(void) {}
void question_4_20(void) {}
void question_4_22(void) {}
void question_4_23(void) {}
void question_4_24(void) {}
void question_4_25(void) {}
void question_4_26(void) {}
void question_4_27(void) {}
void question_4_31(void) {}
void question_4_33(void) {}
void question_4_34(void) {}
void question_4_35(void) {}
void question_4_44(void) {}
void question_4_45(void) {}
void question_4_46(void) {}
