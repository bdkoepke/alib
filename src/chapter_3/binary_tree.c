#include "../contract.h"
#include "binary_tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  tree_vtable *vtable;
  BinaryNode *root;
  Compare c;
} _BinaryTree;

static void binary_tree_free(Object *o) {
  binary_node_free_r(((_BinaryTree *)o)->root);
  free(o);
}

static void *binary_tree_search(const Container *c, const void *x) {
  const _BinaryTree *t = (_BinaryTree *)c;
  return binary_node_search(t->root, t->c, x);
}

static void binary_tree_insert(Container *c, void *x) {
  _BinaryTree *t = (_BinaryTree *)c;
  binary_node_insert(t->root, &(t->root), t->c, x);
}

static void binary_tree_delete(Container *c, const void *x) {
  _BinaryTree *t = (_BinaryTree *)c;
  binary_node_delete(t->root, &(t->root), t->c, x);
}

static bool binary_tree_empty(const Container *c) {
  return binary_node_empty(((_BinaryTree *)c)->root);
}

static void *binary_tree_max(const Dictionary *d) {
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_max(((const _BinaryTree *)d)->root);
}

static void *binary_tree_min(const Dictionary *d) {
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_min(((const _BinaryTree *)d)->root);
}

static void *binary_tree_predecessor(const Dictionary *d, const void *x) {
  const _BinaryTree *t = (const _BinaryTree *)d;
  return binary_node_predecessor(t->root, t->c, x);
}

static void *binary_tree_successor(const Dictionary *d, const void *x) {
  const _BinaryTree *t = (const _BinaryTree *)d;
  return binary_node_successor(t->root, t->c, x);
}

static void binary_tree_pre_order(Tree *t, Visitor v, void *user_data) {
  return binary_node_pre_order(((_BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_in_order(Tree *t, Visitor v, void *user_data) {
  return binary_node_in_order(((_BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_post_order(Tree *t, Visitor v, void *user_data) {
  return binary_node_post_order(((_BinaryTree *)t)->root, v, user_data);
}

static void binary_tree_level_order(Tree *t, Visitor v, void *user_data) {
  return binary_node_level_order(((_BinaryTree *)t)->root, v, user_data);
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

  _BinaryTree *b = malloc(sizeof(_BinaryTree));
  b->vtable = &vtable;
  b->root = NULL;
  b->c = c;
  return (BinaryTree *)b;
}

typedef struct {
  _BinaryTree super;
  void *min;
  void *max;
} MinMaxBinaryTree;

static void min_max_binary_tree_insert(Container *c, void *x) {
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)c;
  if (container_empty(c)) {
    m->min = x;
    m->max = x;
  } else {

    int r = m->super.c(x, m->min);
    if (r < 0)
      m->min = x;
    r = m->super.c(x, m->min);
    if (r > 0)
      m->max = x;
  }
  binary_tree_insert(c, x);
}

static void min_max_binary_tree_delete(Container *c, const void *x) {
  binary_tree_delete(c, x);
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)c;
  if (!container_empty(c)) {
    m->min = dictionary_min((Dictionary *)m);
    m->max = dictionary_max((Dictionary *)m);
  } else {
    m->min = NULL;
    m->max = NULL;
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

static void swap(void **a, void **b) {
  void *temp = *a;
  *a = *b;
  *b = temp;
}

BinaryTree *binary_tree_concatenate(BinaryTree *_a, BinaryTree *_b) {
  _BinaryTree *a = (_BinaryTree *)_a;
  _BinaryTree *b = (_BinaryTree *)_b;
  contract_requires(
      a != NULL && b != NULL && a->c == b->c &&
      (binary_tree_min((Dictionary *)a) > binary_tree_max((Dictionary *)b) ||
       binary_tree_max((Dictionary *)a) < binary_tree_min((Dictionary *)b)));

  if (container_empty((Container *)a))
    return container_empty((Container *)b) ? _a : _b;
  else if (container_empty((Container *)b))
    return _a;

  if (a->c(a->root->x, b->root->x) < 0)
    swap((void **)&a, (void **)&b);
  BinaryNode *n;
  for (n = a->root; n->left != NULL; n = n->left)
    continue;
  n->left = b->root;
  return (BinaryTree *)a;
}
