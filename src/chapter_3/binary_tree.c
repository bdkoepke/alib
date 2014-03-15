#include "../contract.h"
#include "binary_tree.h"

#include <stdbool.h>
#include <stdlib.h>

static void binary_tree_free(Object *o) { contract_requires(false); }

static void *_binary_tree_search(const BinaryNode *n, Compare c,
                                 const void *x) {
  if (n == NULL)
    return NULL;
  int r = c(n->x, x);
  if (r == 0)
    return n->x;
  return r < 0 ? _binary_tree_search(n->left, c, x)
               : _binary_tree_search(n->right, c, x);
}

static void *binary_tree_search(const Container *c, const void *x) {
  const BinaryTree *t = (BinaryTree *)c;
  return _binary_tree_search(t->root, t->c, x);
}

static void _binary_tree_insert(BinaryNode *n, BinaryNode **p, Compare c,
                                void *x) {
  if (n == NULL)
    *p = binary_node_new_leaf(x);
  else {
    int r = c(n->x, x);
    BinaryNode **_p = r < 0 ? &(n->left) : &(n->right);
    _binary_tree_insert(*p, p, c, x);
  }
}

static void binary_tree_insert(Container *c, void *x) {
  BinaryTree *t = (BinaryTree *)c;
  _binary_tree_insert(t->root, &(t->root), t->c, x);
}

static void _binary_tree_delete(BinaryNode *n, BinaryNode **p, Compare c,
                                const void *x) {}

static void binary_tree_delete(Container *c, const void *x) {
  BinaryTree *t = (BinaryTree *)c;
  _binary_tree_delete(t->root, &(t->root), t->c, x);
}

static bool binary_tree_empty(const Container *c) {
  return ((BinaryTree *)c)->root == NULL;
}

static void *binary_tree_max(const Dictionary *d) {
  const BinaryTree *b = (const BinaryTree *)d;
  if (container_empty((Container *)d))
    return NULL;

  const BinaryNode *node;
  for (node = b->root; node->right != NULL; node = node->right)
    continue;
  return node->x;
}

static void *binary_tree_min(const Dictionary *d) {
  const BinaryTree *b = (const BinaryTree *)d;
  if (container_empty((Container *)d))
    return NULL;

  const BinaryNode *node;
  for (node = b->root; node->left != NULL; node = node->left)
    continue;
  return node->x;
}

static void *binary_tree_predecessor(const Dictionary *d, const void *x) {
  return NULL;
}

static void *binary_tree_successor(const Dictionary *d, const void *x) {
  return NULL;
}

void binary_tree_pre_order(Tree *t, Visitor v, void *user_data) {}

void binary_tree_in_order(Tree *t, Visitor v, void *user_data) {}

void binary_tree_post_order(Tree *t, Visitor v, void *user_data) {}

void binary_tree_level_order(Tree *t, Visitor v, void *user_data) {}

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
