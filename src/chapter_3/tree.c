#include "contract.h"
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
