#include "../diag/contract.h"
#include "binary_node.h"
#include "binary_tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct _BinaryTree {
  tree_vtable *vtable;
  BinaryNode *root;
  Compare c;
};

static void binary_tree_free(Object *o) {
  binary_node_free_r(((BinaryTree *)o)->root);
  free(o);
}

static void *binary_tree_search(const Container *c, const void *x) {
  return binary_node_search(((const BinaryTree *)c)->root,
                            ((const BinaryTree *)c)->c, x);
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
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_max(((const BinaryTree *)d)->root);
}

static void *binary_tree_min(const Dictionary *d) {
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_min(((const BinaryTree *)d)->root);
}

static void *binary_tree_predecessor(const Dictionary *d, const void *x) {
  return binary_node_predecessor(((const BinaryTree *)d)->root,
                                 ((const BinaryTree *)d)->c, x);
}

static void *binary_tree_successor(const Dictionary *d, const void *x) {
  return binary_node_successor(((const BinaryTree *)d)->root,
                               ((const BinaryTree *)d)->c, x);
}

static void binary_tree_pre_order(const Tree *t, Visitor v, void *user_data) {
  return binary_node_pre_order(((const BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_in_order(const Tree *t, Visitor v, void *user_data) {
  return binary_node_in_order(((const BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_post_order(const Tree *t, Visitor v, void *user_data) {
  return binary_node_post_order(((const BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_level_order(const Tree *t, Visitor v, void *user_data) {
  return binary_node_level_order(((const BinaryTree *)t)->root, v, user_data);
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
  return (BinaryTree *)b;
}

typedef struct {
  BinaryTree super;
  void *min;
  void *max;
} MinMaxBinaryTree;

static void min_max_binary_tree_insert(Container *c, void *x) {
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)c;
  if (container_empty(c)) {
    m->min = x;
    m->max = x;
  } else {
    Compare _c = m->super.c;
    if (_c(x, m->min) < 0)
      m->min = x;
    if (_c(x, m->max) > 0)
      m->max = x;
  }
  binary_tree_insert(c, x);
}

static void min_max_binary_tree_delete(Container *c, const void *x) {
  binary_tree_delete(c, x);
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)c;
  if (container_empty(c)) {
    m->min = NULL;
    m->max = NULL;
  } else {
    Compare _c = m->super.c;
    if (_c(x, m->min) == 0)
      m->min = binary_tree_min((Dictionary *)m);
    if (_c(x, m->max) == 0)
      m->max = binary_tree_max((Dictionary *)m);
  }
}

static void *min_max_binary_tree_min(const Dictionary *d) {
  return ((MinMaxBinaryTree *)d)->min;
}

static void *min_max_binary_tree_max(const Dictionary *d) {
  return ((MinMaxBinaryTree *)d)->max;
}

BinaryTree *binary_tree_new_fast_min_max(Compare c) {
  static tree_vtable vtable = {
    { { {.free = binary_tree_free },
            .search = binary_tree_search, .insert = min_max_binary_tree_insert,
            .delete = min_max_binary_tree_delete, .empty = binary_tree_empty },
          .max = min_max_binary_tree_max, .min = min_max_binary_tree_min,
          .predecessor = binary_tree_predecessor, .successor =
                                                      binary_tree_successor },
        .pre_order = binary_tree_pre_order, .in_order = binary_tree_in_order,
        .post_order = binary_tree_post_order, .level_order =
                                                  binary_tree_level_order
  };

  contract_requires(c != NULL);

  MinMaxBinaryTree *b = malloc(sizeof(MinMaxBinaryTree));
  b->super.vtable = &vtable;
  b->super.root = NULL;
  b->super.c = c;
  b->min = NULL;
  b->max = NULL;
  return (BinaryTree *)b;
}

BinaryTree *binary_tree_concat(BinaryTree *a, BinaryTree *b) {
  inline void swap(void * *a, void * *b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
  }
  contract_requires(
      a != NULL && b != NULL && a->c == b->c &&
      (binary_tree_min((Dictionary *)a) > binary_tree_max((Dictionary *)b) ||
       binary_tree_max((Dictionary *)a) < binary_tree_min((Dictionary *)b)));

  if (container_empty((Container *)a))
    return container_empty((Container *)b) ? a : b;
  else if (container_empty((Container *)b))
    return a;

  if (a->c(a->root->x, b->root->x) < 0)
    swap((void **)&a, (void **)&b);
  BinaryNode *n;
  for (n = a->root; n->left != NULL; n = n->left)
    continue;
  n->left = b->root;
  free(b);
  return a;
}

bool binary_tree_compare(const BinaryTree *a, const BinaryTree *b) {
  bool binary_node_compare(const BinaryNode * a, const BinaryNode * b,
                           Compare c) {
    if (a == NULL)
      return b == NULL;
    return b == NULL ? false : c(a->x, b->x) == 0 &&
                                   binary_node_compare(a->left, b->left, c) &&
                                   binary_node_compare(a->right, b->right, c);
  }
  return a->c != b->c ? false : binary_node_compare(a->root, b->root, a->c);
}
