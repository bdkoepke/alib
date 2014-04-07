#include "../diag/contract.h"
#include "../lang/type.h"
#include "sparse_array.h"

#include <limits.h>
#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
  unsigned int n;
  unsigned int m;
  unsigned int size;
  unsigned int *A;
  unsigned int *B;
} SparseArray;

static void sparse_array_free(Object *o) {
  SparseArray *s = (SparseArray *)o;
  free(s->A);
  free(s->B);
  free(o);
}

static void sparse_array_insert(Container *c, void *x) {
  SparseArray *s = (SparseArray *)c;
  unsigned int _x = POINTER_TO_INT(x);
  contract_requires(_x < s->n && s->size < UINT_MAX && s->size < s->m);
  contract_weak_requires(container_search((Container *)c, x) ==
                         INT_TO_POINTER(false));
  s->size++;
  s->A[_x] = s->size;
  s->B[s->A[_x] - 1] = _x;
}

static void *sparse_array_search(const Container *c, const void *x) {
  SparseArray *s = (SparseArray *)c;
  unsigned int _x = POINTER_TO_INT(x);
  return (x != NULL && _x < s->n && s->A[_x] != POINTER_TO_INT(NULL) &&
          (s->A[_x] - 1) < s->m && s->B[s->A[_x] - 1] == _x)
             ? INT_TO_POINTER(_x)
             : NULL;
}

static void *sparse_array_delete(Container *c, const void *x) {
  SparseArray *s = (SparseArray *)c;
  unsigned int _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && _x < s->n);
  s->B[s->A[_x] - 1] = POINTER_TO_INT(NULL);
  s->A[_x] = POINTER_TO_INT(NULL);
  s->size--;
	return INT_TO_POINTER(x);
}

static bool sparse_array_empty(const Container *c) {
  return ((SparseArray *)c)->size == 0;
}

Container *sparse_array_new(unsigned int n, unsigned int m) {
  static container_vtable vtable = {
    { {.free = sparse_array_free }, .iterator = NULL },
        .empty = sparse_array_empty, .search = sparse_array_search,
        .delete = sparse_array_delete, .insert = sparse_array_insert
  };

  SparseArray *s = malloc(sizeof(SparseArray));
  s->vtable = &vtable;
  s->size = 0;
  s->n = n;
  s->m = m;
  s->A = malloc(sizeof(unsigned int) * s->n);
  s->B = malloc(sizeof(unsigned int) * s->m);
  return (Container *)s;
}
