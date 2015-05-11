#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.h"

#include <stddef.h>

typedef struct _LinkedStack LinkedStack;

/**
 * Creates a new linked stack.
 *
 * @return a new linked stack.
 */
LinkedStack *linked_stack_new();

/**
 * Reverses the specified stack in place.
 *
 * @param l the stack to reverse.
 */
void linked_stack_reverse(LinkedStack *l);

/**
 * Gets the index of the middle object in the stack.
 *
 * @param l the stack to get the middle object of.
 * @return the index of the middle object.
 */
size_t linked_stack_middle(const LinkedStack *l);

#endif /* LINKED_STACK_H */
