#include "../diag/contract.h"
#include "tree.h"

#include <stdlib.h>

void tree_pre_order(const Tree *t, Visitor v, void *user_data) {
  t->vtable->pre_order(contract_requires_non_null(t),
                       contract_requires_non_null(v), user_data);
}

void tree_in_order(const Tree *t, Visitor v, void *user_data) {
  t->vtable->in_order(contract_requires_non_null(t),
                      contract_requires_non_null(v), user_data);
}

void tree_post_order(const Tree *t, Visitor v, void *user_data) {
  t->vtable->post_order(contract_requires_non_null(t),
                        contract_requires_non_null(v), user_data);
}

void tree_level_order(const Tree *t, Visitor v, void *user_data) {
  t->vtable->level_order(contract_requires_non_null(t),
                         contract_requires_non_null(v), user_data);
}

LinkedStack *tree_to_linked_stack(const Tree *t) {
  void linked_stack_visitor(void * p, const KeyValuePair * x) {
    stack_push((Stack *)p, x->v);
  }
  LinkedStack *l = linked_stack_new();
  tree_in_order((const Tree *)contract_requires_non_null(t),
                linked_stack_visitor, l);
  return l;
}
