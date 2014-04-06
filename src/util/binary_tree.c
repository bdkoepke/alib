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

static void *binary_tree_search(const Container *c, const void *k) {
	const KeyValuePair *p = binary_node_search(((BinaryTree *)c)->root,
                               ((BinaryTree *)c)->c, k);
	return p == NULL ? NULL : p->v;
}

static void binary_tree_insert(Dictionary *s, const void *k, void *v) {
  BinaryTree *t = (BinaryTree *)s;
  binary_node_insert(t->root, &(t->root), t->c, k, v);
}

static void *binary_tree_reassign(Dictionary *s, const void *k, void *v) {
	contract_requires(false);
  return binary_node_reassign(((BinaryTree *)s)->root, ((BinaryTree *)s)->c, k, v);
}

static void binary_tree_delete(Container *c, const void *x) {
  BinaryTree *t = (BinaryTree *)c;
  binary_node_delete(t->root, &(t->root), t->c, x);
}

static bool binary_tree_empty(const Container *c) {
  return binary_node_empty(((BinaryTree *)c)->root);
}

static void *binary_tree_max(const SortedDictionary *s) {
  return container_empty((const Container *)s)
             ? NULL
             : binary_node_max(((const BinaryTree *)s)->root)->v;
}

static void *binary_tree_min(const SortedDictionary *s) {
  return container_empty((const Container *)s)
             ? NULL
             : binary_node_min(((const BinaryTree *)s)->root)->v;
}

static void *binary_tree_predecessor(const SortedDictionary *s, const void *k) {
  const KeyValuePair *p = binary_node_predecessor(((const BinaryTree *)s)->root,
                                              ((const BinaryTree *)s)->c, k);
	return p == NULL ? NULL : p->v;
}

static void *binary_tree_successor(const SortedDictionary *s, const void *x) {
  const KeyValuePair *p = binary_node_successor(((const BinaryTree *)s)->root,
                               ((const BinaryTree *)s)->c, x);
	return p == NULL ? NULL : p->v;
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
    { { { { {.free = binary_tree_free }, .iterator = NULL },
            .search = binary_tree_search, .empty = binary_tree_empty,
            .delete = binary_tree_delete, .insert = _container_insert },
					.insert = binary_tree_insert, .reassign = binary_tree_reassign
					},
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
  KeyValuePair min;
  KeyValuePair max;
} MinMaxBinaryTree;

static void *min_max_binary_tree_reassign(Dictionary *d, const void *k, void *v) {
	contract_requires(false);
}

static void min_max_binary_tree_insert(Dictionary *d, const void *k, void *v) {
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)d;
  if (container_empty((Container *)m)) {
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

static void min_max_binary_tree_delete(Container *c, const void *x) {
  binary_tree_delete(c, x);
  MinMaxBinaryTree *m = (MinMaxBinaryTree *)c;
  if (container_empty((Container *)c)) {
    m->min.k = m->min.v = NULL;
    m->max.k = m->max.v = NULL;
  } else {
    Compare _c = m->super.c;
    if (_c(x, m->min.k) == 0)
      m->min = *binary_node_min(m->super.root);
    if (_c(x, m->max.k) == 0)
      m->max = *binary_node_max(m->super.root);
  }
}

static void *min_max_binary_tree_min(const SortedDictionary *d) {
  return ((MinMaxBinaryTree *)d)->min.v;
}

static void *min_max_binary_tree_max(const SortedDictionary *d) {
  return ((MinMaxBinaryTree *)d)->max.v;
}

BinaryTree *binary_tree_new_fast_min_max(Compare c) {
  static tree_vtable vtable = {
    { { { { {.free = binary_tree_free }, .iterator = NULL },
            .search = binary_tree_search, .empty = binary_tree_empty,
            .insert = _container_insert,
            .delete = min_max_binary_tree_delete },
					.insert = min_max_binary_tree_insert,
					.reassign = min_max_binary_tree_reassign
					},
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
	b->min.k = NULL, b->min.v = NULL;
	b->max.k = NULL, b->max.v = NULL;
  return (BinaryTree *)b;
}

BinaryTree *binary_tree_concat(BinaryTree *a, BinaryTree *b) {
  inline void swap(void * *a, void * *b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
  }
	/*
  contract_requires(
      a != NULL && b != NULL && a->c == b->c &&
      (binary_tree_min((Dictionary *)a)->k > binary_tree_max((Dictionary *)b)->k ||
       binary_tree_max((Dictionary *)a) < binary_tree_min((Dictionary *)b)));
	*/

  if (container_empty((Container *)a))
    return container_empty((Container *)b) ? a : b;
  else if (container_empty((Container *)b))
    return a;

  if (a->c(a->root->p.k, b->root->p.k) < 0)
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
    return b == NULL ? false : c(a->p.k, b->p.k) == 0 &&
                                   binary_node_compare(a->left, b->left, c) &&
                                   binary_node_compare(a->right, b->right, c);
  }
  return a->c != b->c ? false : binary_node_compare(a->root, b->root, a->c);
}
