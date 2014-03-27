#include "../diag/contract.h"
#include "../lang/type.h"
#include "../util/linked_queue.h"
#include "sort.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	contract_requires(a != NULL && b != NULL);
  int t = *a;
	*a = *b, *b = t;
}

void selectionsort(int a[], size_t length) {
	contract_requires(a != NULL);
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

void insertionsort(int a[], size_t length) {
	contract_requires(a != NULL);
  int i, j;
  for (i = 1; i < length; i++)
    for (j = i; j > 0 && a[j - 1] > a[j]; j--)
      swap(&a[j], &a[j - 1]);
}

void mergesort(int a[], size_t length) {
  void _mergesort(int a[], int l, int h) {
    void merge(int a[], int l, int m, int h) {
      Queue *lq = linked_queue_new();
      Queue *hq = linked_queue_new();

      size_t i;
      for (i = l; i <= m; i++)
        queue_enqueue(lq, INT_TO_POINTER(a[i]));
      for (; i <= h; i++)
        queue_enqueue(hq, INT_TO_POINTER(a[i]));

      inline bool queue_empty(const Queue * q) {
        return container_empty((const Container *)q);
      }

      for (i = l; !queue_empty(lq) && !queue_empty(hq); i++)
        a[i] = POINTER_TO_INT(queue_dequeue(
            POINTER_TO_INT(queue_head(lq)) <= POINTER_TO_INT(queue_head(hq))
                ? lq
                : hq));

      for (; !queue_empty(lq); i++)
        a[i] = POINTER_TO_INT(queue_dequeue(lq));
      for (; !queue_empty(hq); i++)
        a[i] = POINTER_TO_INT(queue_dequeue(hq));
    }

    if (l < h) {
      size_t m = (l + h) / 2;
      _mergesort(a, l, m);
      _mergesort(a, m + 1, h);
      merge(a, l, m, h);
    }
  }
	contract_requires(a != NULL);
  return _mergesort(a, 0, length - 1);
}

static int partition(int a[], size_t l, size_t h) {
	size_t p = h;
	int _h = l;

	size_t i;
	for (i = l; i < h; i++)
		if (a[i] < a[p]) {
			swap(&a[i], &a[_h]);
			_h++;
		}
	swap(&a[p], &a[_h]);
	return _h;
}

int quickselect(int a[], size_t length, size_t k) {
	int qs(int a[], size_t l, size_t h, size_t k) {
		int p = partition(a, l, h);
		if (k == p)
			return a[p];
		return k < p ? qs(a, l, p - 1, k) : qs(a, p + 1, h, k);
	}
	contract_requires(a != NULL && k < length);
	return qs(a, 0, length, k);
}

void quicksort(int a[], size_t length) {
  void _quicksort(int a[], size_t l, size_t h) {
    if (l < h) {
      int p = partition(a, l, h);
      _quicksort(a, l, p == 0 ? 0 : p - 1);
      _quicksort(a, p + 1, h);
    }
  }
	contract_requires(a != NULL);
  return _quicksort(a, 0, length - 1);
}

int *buckets_new(int a[], size_t length, int max) {
	contract_requires(a != NULL);
  int *s = calloc(max + 1, sizeof(int));
  size_t i;
  for (i = 0; i < length; i++)
    s[a[i]]++;
  return s;
}

void bucketsort(int a[], size_t length, int max) {
	contract_requires(a != NULL);
  int s[max + 1];

  size_t i, j, k;
  for (i = 0; i <= max; i++)
    s[i] = 0;
  for (i = 0; i < length; i++)
    s[a[i]]++;

  j = 0;
  for (i = 0; i <= max; i++)
    for (k = 0; k < s[i]; k++)
      a[j++] = i;
}
