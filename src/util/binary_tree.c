#include "../diag/contract.h"
#include "binary_node.h"
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

static void *binary_tree_search(const Dictionary *d, const void *k) {
  const KeyValuePair *p =
      binary_node_search(((_BinaryTree *)d)->root, ((_BinaryTree *)d)->c, k);
  return p == NULL ? NULL : p->v;
}

static void binary_tree_insert(Dictionary *s, const void *k, void *v) {
  _BinaryTree *t = (_BinaryTree *)s;
  binary_node_insert(t->root, &(t->root), t->c, k, v);
}

static void *binary_tree_reassign(Dictionary *s, const void *k, void *v) {
  return binary_node_reassign(((_BinaryTree *)s)->root, ((_BinaryTree *)s)->c,
                              k, v);
}

static void *binary_tree_delete(Dictionary *d, const void *x) {
  _BinaryTree *t = (_BinaryTree *)d;
  return binary_node_delete(t->root, &(t->root), t->c, x);
}

static bool binary_tree_empty(const Set *s) {
  return binary_node_empty(((_BinaryTree *)s)->root);
}

static void *binary_tree_max(const SortedDictionary *s) {
  return set_empty((Set *)s)
             ? NULL
             : binary_node_max(((const _BinaryTree *)s)->root)->v;
}

static void *binary_tree_min(const SortedDictionary *s) {
  return set_empty((Set *)s)
             ? NULL
             : binary_node_min(((const _BinaryTree *)s)->root)->v;
}

static void *binary_tree_predecessor(const SortedDictionary *s, const void *k) {
  const KeyValuePair *p = binary_node_predecessor(
      ((const _BinaryTree *)s)->root, ((const _BinaryTree *)s)->c, k);
  return p == NULL ? NULL : p->v;
}

static void *binary_tree_successor(const SortedDictionary *s, const void *x) {
  const KeyValuePair *p = binary_node_successor(((const _BinaryTree *)s)->root,
                                                ((const _BinaryTree *)s)->c, x);
  return p == NULL ? NULL : p->v;
}

static Iterator *binary_tree_pre_order(const Tree *t) {
  return binary_node_pre_order(((const _BinaryTree *)t)->root);
}

static Iterator *binary_tree_in_order(const Tree *t) {
  return binary_node_in_order(((const _BinaryTree *)t)->root);
}

static Iterator *binary_tree_post_order(const Tree *t) {
  return binary_node_post_order(((const _BinaryTree *)t)->root);
}

static Iterator *binary_tree_level_order(const Tree *t) {
  return binary_node_level_order(((const _BinaryTree *)t)->root);
}

static Iterator *binary_tree_iterator(const Iterable *i) {
  return binary_node_post_order(((const _BinaryTree *)i)->root);
}

BinaryTree *binary_tree_new(Compare c) {
  static tree_vtable vtable = {
    { { { { { .free = binary_tree_free }, .iterator = binary_tree_iterator, },
          .search = _dictionary_set_search,
          .insert = _dictionary_set_insert,
          .delete = _dictionary_set_delete,
          .empty = binary_tree_empty },
        .search = binary_tree_search, .delete = binary_tree_delete,
        .insert = binary_tree_insert, .reassign = binary_tree_reassign },
      .max = binary_tree_max, .min = binary_tree_min,
      .predecessor = binary_tree_predecessor,
      .successor = binary_tree_successor },
    .pre_order = binary_tree_pre_order, .in_order = binary_tree_in_order,
    .post_order = binary_tree_post_order, .level_order = binary_tree_level_order
  };

  _BinaryTree *b = malloc(sizeof(_BinaryTree));
  b->c = contract_requires_non_null(c);
  b->vtable = &vtable;
  b->root = NULL;
  return (BinaryTree *)b;
}

typedef struct {
  _BinaryTree super;
  KeyValuePair min;
  KeyValuePair max;
} MinMaxBinaryTree;

static void *min_max_binary_tree_reassign(Dictionary *d, const void *k,
                                          void *v) {
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)d;
  if (set_empty((Set *)d)) {
    m->min.k = k, m->min.v = v;
    m->max.k = k, m->max.v = v;
  } else {
    Compare c = m->super.c;
    if (c(k, m->min.k) < 0)
      m->min.k = k, m->min.v = v;
    if (c(k, m->max.k) > 0)
      m->max.k = k, m->max.v = v;
  }
  return binary_tree_reassign(d, k, v);
}

static void min_max_binary_tree_insert(Dictionary *d, const void *k, void *v) {
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)d;
  if (set_empty((Set *)d)) {
    m->min.k = k, m->min.v = v;
    m->max.k = k, m->max.v = v;
  } else {
    Compare c = m->super.c;
    if (c(k, m->min.k) < 0)
      m->min.k = k, m->min.v = v;
    if (c(k, m->max.k) > 0)
      m->max.k = k, m->max.v = v;
  }
  binary_tree_insert(d, k, v);
}

static void *min_max_binary_tree_delete(Dictionary *d, const void *x) {
  void *o = binary_tree_delete(d, x);
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)d;
  if (set_empty((Set *)d)) {
    m->min.k = (m->min.v = NULL);
    m->max.k = (m->max.v = NULL);
  } else {
    Compare _c = m->super.c;
    if (_c(x, m->min.k) == 0)
      m->min = *binary_node_min(m->super.root);
    if (_c(x, m->max.k) == 0)
      m->max = *binary_node_max(m->super.root);
  }
  return o;
}

static void *min_max_binary_tree_min(const SortedDictionary *d) {
  return ((MinMaxBinaryTree *)d)->min.v;
}

static void *min_max_binary_tree_max(const SortedDictionary *d) {
  return ((MinMaxBinaryTree *)d)->max.v;
}

BinaryTree *binary_tree_new_fast_min_max(Compare c) {
  static tree_vtable vtable = {
    { { { { { .free = binary_tree_free }, .iterator = binary_tree_iterator },
          .insert = _dictionary_set_insert,
          .search = _dictionary_set_search,
          .delete = _dictionary_set_delete,
          .empty = binary_tree_empty },
        .search = binary_tree_search, .delete = min_max_binary_tree_delete,
        .insert = min_max_binary_tree_insert,
        .reassign = min_max_binary_tree_reassign },
      .max = min_max_binary_tree_max, .min = min_max_binary_tree_min,
      .predecessor = binary_tree_predecessor,
      .successor = binary_tree_successor },
    .pre_order = binary_tree_pre_order, .in_order = binary_tree_in_order,
    .post_order = binary_tree_post_order, .level_order = binary_tree_level_order
  };

  MinMaxBinaryTree *b = malloc(sizeof(MinMaxBinaryTree));
  b->super.c = contract_requires_non_null(c);
  b->super.vtable = &vtable;
  b->super.root = NULL;
  b->min.k = NULL, b->min.v = NULL;
  b->max.k = NULL, b->max.v = NULL;
  return (BinaryTree *)b;
}

static void swap(void **a, void **b) {
  void *temp = *a;
  *a = *b;
  *b = temp;
}

BinaryTree *binary_tree_concat(BinaryTree *a, BinaryTree *b) {

  if (set_empty((Set *)a))
    return set_empty((Set *)b) ? a : b;
  else if (set_empty((Set *)b))
    return a;

  if (((_BinaryTree *)a)
          ->c(((_BinaryTree *)a)->root->p.k, ((_BinaryTree *)b)->root->p.k) < 0)
    swap((void **)&a, (void **)&b);
  BinaryNode *n;
  for (n = ((_BinaryTree *)a)->root; n->left != NULL; n = n->left)
    continue;
  n->left = ((_BinaryTree *)b)->root;
  free(b);
  return a;
}

static bool binary_node_compare(const BinaryNode *a, const BinaryNode *b,
                                Compare c) {
  if (a == NULL)
    return b == NULL;
  return b == NULL ? false : c(a->p.k, b->p.k) == 0 &&
                                 binary_node_compare(a->left, b->left, c) &&
                                 binary_node_compare(a->right, b->right, c);
}

bool binary_tree_compare(const BinaryTree *a, const BinaryTree *b) {

  return ((_BinaryTree *)a)->c != ((_BinaryTree *)b)->c
             ? false
             : binary_node_compare(((_BinaryTree *)a)->root,
                                   ((_BinaryTree *)b)->root,
                                   ((_BinaryTree *)a)->c);
}
