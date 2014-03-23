#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "container.h"

#include <stddef.h>

typedef struct _array_list_vtable array_list_vtable;
typedef struct ArrayList {
  array_list_vtable *vtable;
} ArrayList;
struct _array_list_vtable {
  container_vtable container;
  void (*set)(ArrayList *, size_t, void *);
  void *(*get)(const ArrayList *, size_t);
  size_t (*size)(const ArrayList *);
};

ArrayList *array_list_new();

size_t array_list_size(const ArrayList *);
void array_list_set(ArrayList *, size_t, void *);
void *array_list_get(const ArrayList *, size_t);

void *_array_list_search(const Container *, const void *);
bool _array_list_empty(const Container *);

#endif /* ARRAY_LIST_H */
