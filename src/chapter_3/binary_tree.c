#include "../contract.h"
#include "binary_tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void binary_tree_free(Object *o) {
	binary_node_free_r(((BinaryTree *)o)->root);
	free(o);
}

static void *binary_tree_search(const Container *c, const void *x) {
  const BinaryTree *t = (BinaryTree *)c;
  return binary_node_search(t->root, t->c, x);
}

static void binary_tree_insert(Container *c, void *x) {
  BinaryTree *t = (BinaryTree *)c;
  binary_node_insert(t->root, &(t->root), t->c, x);
}

static void binary_tree_delete(Container *c, const void *x) {
  BinaryTree *t = (BinaryTree *)c;
  binary_node_delete(t->root, &(t->root), t->c, x);
}

static bool binary_tree_empty(const Container *c) {
  return binary_node_empty(((BinaryTree *)c)->root);
}

static void *binary_tree_max(const Dictionary *d) {
  return container_empty((const Container *)d) ? NULL : binary_node_max(((const BinaryTree *)d)->root);
}

static void *binary_tree_min(const Dictionary *d) {
  return container_empty((const Container *)d) ? NULL : binary_node_min(((const BinaryTree *)d)->root);
}

static void *binary_tree_predecessor(const Dictionary *d, const void *x) {
	const BinaryTree *t = (const BinaryTree *)d;
	return binary_node_predecessor(t->root, t->c, x);
}

static void *binary_tree_successor(const Dictionary *d, const void *x) {
	const BinaryTree *t = (const BinaryTree *)d;
	return binary_node_successor(t->root, t->c, x);
}

static void binary_tree_pre_order(Tree *t, Visitor v, void *user_data) {
	return binary_node_pre_order(((BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_in_order(Tree *t, Visitor v, void *user_data) {
	return binary_node_in_order(((BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_post_order(Tree *t, Visitor v, void *user_data) {
	return binary_node_post_order(((BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_level_order(Tree *t, Visitor v, void *user_data) {
	return binary_node_level_order(((BinaryTree *)t)->root, v, user_data);
}

BinaryTree *binary_tree_new(Compare c) {
  static tree_vtable vtable = {
    { { {.free = binary_tree_free },
            .search = binary_tree_search, .insert = binary_tree_insert,
            .delete = binary_tree_delete, .empty = binary_tree_empty },
          .max = binary_tree_max, .min = binary_tree_min,
          .predecessor = binary_tree_predecessor, .successor =
                                                      binary_tree_successor },
        .pre_order = binary_tree_pre_order, .in_order = binary_tree_in_order,
        .post_order = binary_tree_post_order, .level_order =
                                                  binary_tree_level_order
  };

  contract_requires(c != NULL);

  BinaryTree *b = malloc(sizeof(BinaryTree));
  b->vtable = &vtable;
  b->root = NULL;
  b->c = c;
  return b;
}
