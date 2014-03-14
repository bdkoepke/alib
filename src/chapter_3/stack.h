#ifndef STACK_H
#define STACK_H

#include "object.h"

#include <stdbool.h>

typedef struct _stack_vtable stack_vtable;
typedef struct Stack {
  stack_vtable *vtable;
} Stack;
struct _stack_vtable {
  object_vtable object;
  void (*push)(Stack *, void *);
  void *(*pop)(Stack *);
  bool (*empty)(const Stack *);
};

Stack *stack_new();

void stack_push(Stack *, void *);
void *stack_pop(Stack *);
bool stack_empty(const Stack *);

void _stack_free(Object *);

#endif /* STACK_H */
