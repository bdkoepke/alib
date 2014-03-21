#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.h"

#include <stddef.h>

typedef struct _LinkedStack LinkedStack;

LinkedStack *linked_stack_new();

void linked_stack_reverse(LinkedStack *);
size_t linked_stack_middle(const LinkedStack *);

#endif /* LINKED_STACK_H */
