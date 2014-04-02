#include "../diag/contract.h"
#include "../lang/type.h"
#include "array_container.h"

#include <stdlib.h>

typedef struct {
  mutable_container_vtable *vtable;
  void **array;
  size_t length;
  size_t size;
} ArrayContainer;

static void array_container_free(Object *o) {
  free(((ArrayContainer *)o)->array);
  free(o);
}

static void array_container_insert(MutableContainer *c, void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && _x <= a->length);
  contract_weak_requires(container_search((Container *)c, x) == INT_TO_POINTER(false));
  a->array[_x - 1] = x;
  a->size++;
}

static void *array_container_search(const Container *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  return _x <= a->length ? a->array[_x - 1] : NULL;
}

static void array_container_delete(MutableContainer *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && _x <= a->length);
  a->size--;
  a->array[_x - 1] = NULL;
}

static bool array_container_empty(const Container *c) {
  return ((ArrayContainer *)c)->size == 0;
}

MutableContainer *array_container_new(size_t length) {
  static mutable_container_vtable vtable = {
    { {.free = array_container_free },
			.search = array_container_search,
			.empty = array_container_empty },
      .insert = array_container_insert,
			.delete = array_container_delete,
  };

  // TODO: should be possible to create a lower bound to, so you could have an
  // array that requires 1999-2010, etc.
  ArrayContainer *array = malloc(sizeof(ArrayContainer));
  array->vtable = &vtable;
  array->array = calloc(length, sizeof(void *));
  array->length = length;
  array->size = 0;
  return (MutableContainer *)array;
}
