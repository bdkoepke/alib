#ifndef STACK_H
#define STACK_H

#include "container.h"

#include <stdbool.h>

typedef struct _stack_vtable stack_vtable;
typedef struct Stack {
  stack_vtable *vtable;
} Stack;
struct _stack_vtable {
	container_vtable container;
  void (*push)(Stack *, void *);
  void *(*pop)(Stack *);
	const void *(*peek)(const Stack *);
	void (*reverse)(Stack *);
};

Stack *stack_new();

void stack_push(Stack *, void *);
void *stack_pop(Stack *);
const void *stack_peek(const Stack *);
void stack_reverse(Stack *);

void _stack_insert(Container *, void *);

void _stack_free(Object *);

#endif /* STACK_H */
