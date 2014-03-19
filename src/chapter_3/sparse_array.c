#include "array_container.h"
#include "contract.h"
#include "type.h"

#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
	size_t n;
	size_t m;
	void **A;
	void **B;
} SparseArray;

static void sparse_array_free(Object *o) {
  free(o);
}

static void sparse_array_insert(Container *c, void *x) {
  SparseArray *s = (SparseArray *)c;
  size_t _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && container_search(c, x) ==
                                     INT_TO_POINTER(false) && _x <= s->n);
}

static void *sparse_array_search(const Container *c, const void *x) {
  SparseArray *s = (SparseArray *)c;
  size_t _x = POINTER_TO_INT(x);
}

static void sparse_array_delete(Container *c, const void *x) {
  SparseArray *s = (SparseArray *)c;
  size_t _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && _x <= s->n);
}

static bool sparse_array_empty(const Container *c) {
}

Container *sparse_array_new(size_t n) {
  static container_vtable vtable = {
    {.free = sparse_array_free },
        .insert = sparse_array_insert, .search = sparse_array_search,
        .delete = sparse_array_delete, .empty = sparse_array_empty
  };

  SparseArray *s = malloc(sizeof(SparseArray));
	s->vtable = &vtable;
	s->n = n;
  return (Container *)s;
}
