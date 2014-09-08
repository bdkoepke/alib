#include "../diag/contract.h"
#include "key_value_pair.h"
#include "linked_stack.h"
#include "tree.h"

#include <stdlib.h>

typedef Iterator *(*TreeIterator)(const Tree *t);

static Iterator *tree_iterator(const Tree *t, TreeIterator i) {
  return contract_ensures_non_null(i(contract_requires_non_null(t)));
}

Iterator *tree_pre_order(const Tree *t) {
  return tree_iterator(t, t->vtable->pre_order);
}

Iterator *tree_in_order(const Tree *t) {
  return tree_iterator(t, t->vtable->in_order);
}

Iterator *tree_post_order(const Tree *t) {
  return tree_iterator(t, t->vtable->post_order);
}

Iterator *tree_level_order(const Tree *t) {
  return tree_iterator(t, t->vtable->level_order);
}

static void linked_stack_visitor(void *p, void *x) {
  stack_push((Stack *)p, ((KeyValuePair *)x)->v);
}

LinkedStack *tree_to_linked_stack(const Tree *t) {
  LinkedStack *l = linked_stack_new();
  Iterator *i = tree_in_order(contract_requires_non_null(t));
  iterator_foreach(i, linked_stack_visitor, l);
  object_free((Object *)i);
  return l;
}
