#ifndef STACK_H
#define STACK_H

#include "mutable_container.h"

#include <stdbool.h>

typedef struct _stack_vtable stack_vtable;
typedef struct Stack {
  stack_vtable *vtable;
} Stack;
struct _stack_vtable {
  mutable_container_vtable container;
  void (*push)(Stack *, void *);
  void *(*pop)(Stack *);
  const void *(*peek)(const Stack *);
};

/**
 * Pushes the specified object onto the stack.
 *
 * @param s the stack to push the object onto.
 * @param x the object to push onto the stack.
 */
void stack_push(Stack *s, void *x);

/**
 * Removes and returns the top object from the stack.
 *
 * @param s the stack to get the object from.
 * @return the object on the top of the stack.
 */
void *stack_pop(Stack *s);

/**
 * Retrieves but does not remove the top object from the stack.
 *
 * @param s the stack to get the object from.
 * @return the object on the top of the stack.
 */
const void *stack_peek(const Stack *s);

void _stack_insert(MutableContainer *c, void *x);

void _stack_free(Object *o);

#endif /* STACK_H */
