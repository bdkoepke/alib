#include "../diag/contract.h"
#include "tree.h"

#include <stdlib.h>

void tree_pre_order(Tree *t, Visitor v, void *user_data) {
  contract_requires(t != NULL && v != NULL);
  t->vtable->pre_order(t, v, user_data);
}

void tree_in_order(Tree *t, Visitor v, void *user_data) {
  contract_requires(t != NULL && v != NULL);
  t->vtable->in_order(t, v, user_data);
}

void tree_post_order(Tree *t, Visitor v, void *user_data) {
  contract_requires(t != NULL && v != NULL);
  t->vtable->post_order(t, v, user_data);
}

void tree_level_order(Tree *t, Visitor v, void *user_data) {
  contract_requires(t != NULL && v != NULL);
  t->vtable->level_order(t, v, user_data);
}

static void linked_stack_visitor(void *p, void *x) {
  stack_push((Stack *)p, x);
}

LinkedStack *tree_to_linked_stack(Tree *t) {
	LinkedStack *l = linked_stack_new();
	tree_in_order(t, linked_stack_visitor, l);
	return l;
}
