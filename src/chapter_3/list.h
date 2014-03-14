#ifndef LIST_H
#define LIST_H

#include "container.h"

typedef struct _list_vtable list_vtable;
typedef struct List {
  list_vtable *vtable;
} List;
struct _list_vtable {
  container_vtable container;
  void *(*car)(const List *);
  void (*cdr)(List *);
  void (*reverse)(List *);
};

List *list_new();

void *list_car(const List *);
void list_cdr(List *);
void *list_cadr(List *);
void list_reverse(List *);

#endif /* LIST_H */
