#include "contract.h"
#include "sparse_array.h"
#include "type.h"

#include <limits.h>
#include <stdlib.h>

typedef struct {
  array_vtable *vtable;
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
  contract_requires(container_search(c, x) == INT_TO_POINTER(false) &&
                    _x < s->n && s->size < UINT_MAX && s->size < s->m);
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

static void sparse_array_set(Array *a, size_t i, void *x) {
  ((SparseArray *)a)->B[((SparseArray *)a)->A[i] - 1] = POINTER_TO_INT(x);
}

static void *sparse_array_get(const Array *a, size_t i) {
  SparseArray *s = (SparseArray *)a;
  return (i != POINTER_TO_INT(NULL) && i < s->n &&
          s->A[i] != POINTER_TO_INT(NULL) && (s->A[i] - 1) < s->m &&
          s->B[s->A[i] - 1] == i)
             ? INT_TO_POINTER(i)
             : NULL;
}

static void sparse_array_delete(Container *c, const void *x) {
  SparseArray *s = (SparseArray *)c;
  unsigned int _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && _x < s->n);
  s->B[s->A[_x] - 1] = POINTER_TO_INT(NULL);
  s->A[_x] = POINTER_TO_INT(NULL);
  s->size--;
}

static size_t sparse_array_size(const Array *a) {
  SparseArray *s = (SparseArray *)a;
  return s->size;
}

Array *sparse_array_new(unsigned int n, unsigned int m) {
  static array_vtable vtable = {
    { {.free = sparse_array_free },
          .insert = sparse_array_insert, .search = sparse_array_search,
          .delete = sparse_array_delete, .empty = _array_empty },
        .set = sparse_array_set, .get = sparse_array_get, .size =
                                                              sparse_array_size
  };

  SparseArray *s = malloc(sizeof(SparseArray));
  s->vtable = &vtable;
  s->size = 0;
  s->n = n;
  s->m = m;
  s->A = malloc(sizeof(unsigned int) * s->n);
  s->B = malloc(sizeof(unsigned int) * s->m);
  return (Array *)s;
}
