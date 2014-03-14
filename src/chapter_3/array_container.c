#include "array_container.h"
#include "contract.h"
#include "type.h"

#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
  void **array;
  size_t length;
  size_t size;
} ArrayContainer;

static void array_container_free(Object *o) {
  free(((ArrayContainer *)o)->array);
  free(o);
}

static void array_container_insert(Container *c, void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  contract_requires(x != NULL && container_search(c, x) ==
                                     INT_TO_POINTER(false) && a->length < _x);
  a->array[_x] = x;
  a->size++;
}

static void *array_container_search(const Container *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  return _x < a->length ? a->array[_x] : NULL;
}

static void array_container_delete(Container *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  a->size--;
  a->array[POINTER_TO_INT(x)] = NULL;
}

static bool array_container_empty(const Container *c) {
  return ((ArrayContainer *)c)->size == 0;
}

Container *array_container_new(size_t length) {
  static container_vtable vtable = {
    {.free = array_container_free }, .insert = array_container_insert,
                                         .search = array_container_search,
                                         .delete = array_container_delete
  };

  ArrayContainer *array = malloc(sizeof(ArrayContainer));
  array->vtable = &vtable;
  array->array = calloc(length, sizeof(void *));
  array->length = length;
  array->size = 0;
  return (Container *)array;
}
