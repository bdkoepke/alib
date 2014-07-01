#include "../diag/contract.h"
#include "../lang/type.h"
#include "array_container.h"

#include <stdlib.h>

typedef struct {
  container_vtable *vtable;
  void **array;
  size_t length;
  size_t size;
} ArrayContainer;

typedef struct {
  iterator_vtable *vtable;
  ArrayContainer *a;
  size_t i;
} ArrayContainerIterator;

static void *array_container_iterator_current(const Iterator *i) {
  const ArrayContainerIterator *a = (const ArrayContainerIterator *)i;
  return a->a->array[a->i];
}

static iterator_vtable vtable_invalid_state = {
  { .class = "array_container_iterator",
    .free = _object_free,
    .to_string = _object_to_string },
  .current = _iterator_current_invalid_state,
  .move_next = _iterator_move_next_invalid_state
};

static bool array_container_iterator_move_next(Iterator *i) {
  ArrayContainerIterator *a = (ArrayContainerIterator *)i;
  a->i++;
  if (a->i < a->a->size)
    return true;
  i->vtable = &vtable_invalid_state;
  return false;
}

static bool array_container_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = { { .class = "array_container_iterator",
                                      .free = _object_free,
                                      .to_string = _object_to_string },
                                    .current = array_container_iterator_current,
                                    .move_next =
                                        array_container_iterator_move_next };
  // we already know that there is at least one element in the
  // container (determined in the constructor). This would result
  // in a hard-failure at runtime if it was false, but this is
  // a contract violation anyway so we consider it to be a weak
  // requirement.
  contract_weak_requires(
      !container_empty((Container *)((ArrayContainerIterator *)i)->a));
  i->vtable = &vtable;
  return true;
}

static Iterator *array_container_iterator(const Iterable *i) {
  static iterator_vtable vtable = {
    { .class = "array_container_iterator",
      .free = _object_free,
      .to_string = _object_to_string },
    .current = _iterator_current_invalid_state,
    .move_next = array_container_iterator_move_next_init
  };
  ArrayContainerIterator *a = malloc(sizeof(ArrayContainerIterator));
  a->a = (ArrayContainer *)i;
  a->i = 0;
  a->vtable = container_empty((Container *)i) ? &vtable_invalid_state : &vtable;
  return (Iterator *)a;
}

static void array_container_free(Object *o) {
  free(((ArrayContainer *)o)->array);
  free(o);
}

static void array_container_insert(Container *c, void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x;
  contract_requires((_x = POINTER_TO_INT(contract_requires_non_null(x))) <=
                    a->length);
  contract_weak_requires(container_search((Container *)c, x) ==
                         INT_TO_POINTER(false));
  a->array[_x - 1] = x;
  a->size++;
}

static void *array_container_search(const Container *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x = POINTER_TO_INT(x);
  return _x <= a->length ? a->array[_x - 1] : NULL;
}

static void *array_container_delete(Container *c, const void *x) {
  ArrayContainer *a = (ArrayContainer *)c;
  size_t _x;
  contract_requires((_x = POINTER_TO_INT(contract_requires_non_null(x))) <=
                    a->length);
  a->size--;
  void *o = a->array[_x - 1];
  a->array[_x - 1] = NULL;
  return o;
}

static bool array_container_empty(const Container *c) {
  return ((ArrayContainer *)c)->size == 0;
}

Container *array_container_new(size_t length) {
  static container_vtable vtable = { { { .class = "array_container",
                                         .free = array_container_free,
                                         .to_string = _object_to_string },
                                       .iterator = array_container_iterator },
                                     .search = array_container_search,
                                     .empty = array_container_empty,
                                     .insert = array_container_insert,
                                     .delete = array_container_delete };
  // TODO: should be possible to create a lower bound to, so you could have an
  // array that requires 1999-2010, etc.
  ArrayContainer *array = malloc(sizeof(ArrayContainer));
  array->vtable = &vtable;
  array->array = calloc(length, sizeof(void *));
  array->length = length;
  array->size = 0;
  return (Container *)array;
}
