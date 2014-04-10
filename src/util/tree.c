#include "../diag/contract.h"
#include "tree.h"

#include <stdlib.h>

typedef Iterator *(*TreeIterator)(const Tree *t);

static inline Iterator *tree_iterator(const Tree *t, TreeIterator i) {
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

LinkedStack *tree_to_linked_stack(const Tree *t) {
  void linked_stack_visitor(void * p, void * x) {
    stack_push((Stack *)p, ((KeyValuePair *)x)->v);
  }

  LinkedStack *l = linked_stack_new();
  iterator_foreach(tree_in_order(contract_requires_non_null(t)),
                   linked_stack_visitor, l);
  return l;
}
