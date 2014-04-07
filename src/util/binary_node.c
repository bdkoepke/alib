#include "../diag/contract.h"
#include "binary_node.h"
#include "linked_queue.h"

#include <stdlib.h>

BinaryNode *binary_node_new(const void *k, void *v, BinaryNode *left, BinaryNode *right) {
  BinaryNode *n = malloc(sizeof(BinaryNode));
  n->p.k = k, n->p.v = v;
  n->left = left;
  n->right = right;
  return n;
}

BinaryNode *binary_node_new_leaf(const void *k, void *v) {
  return binary_node_new(k, v, NULL, NULL);
}

bool binary_node_is_leaf(const BinaryNode *n) {
  return n->left == NULL && n->right == NULL;
}

bool binary_node_is_branch(const BinaryNode *n) {
  return n->left != NULL && n->right != NULL;
}

void binary_node_free_r(BinaryNode *n) {
  if (n != NULL) {
    binary_node_free_r(n->left);
    binary_node_free_r(n->right);
    free(n);
  }
}

void binary_node_insert(BinaryNode *n, BinaryNode **p, Compare c, const void *k, void *v) {
  if (n == NULL)
    *p = binary_node_new_leaf(k, v);
  else {
    int r = c(k, n->p.k);
    BinaryNode **_p = r < 0 ? &(n->left) : &(n->right);
    binary_node_insert(*_p, _p, c, k, v);
  }
}

void *binary_node_reassign(BinaryNode *n, Compare c, const void *k, void *v) {
	contract_requires(n != NULL);
	int r = c(k, n->p.k);
	if (r == 0) {
		void *o = n->p.v;
		n->p.v = v;
		return o;
	}
	else
		return binary_node_reassign(r < 0 ? n->left : n->right, c, k, v);
}

KeyValuePair const *binary_node_search(const BinaryNode *n, Compare c, const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return &(n->p);
  return r < 0 ? binary_node_search(n->left, c, k)
               : binary_node_search(n->right, c, k);
}

void *binary_node_delete(BinaryNode *n, BinaryNode **p, Compare c,
                        const void *k) {
  int r = c(k, n->p.k);
  if (r < 0)
    return binary_node_delete(n->left, &(n->left), c, k);
  else if (r > 0)
    return binary_node_delete(n->right, &(n->right), c, k);
  else {
    if (binary_node_is_branch(n)) {
      n->p = *binary_node_min(n->right);
      return binary_node_delete(n->right, &(n->right), c, n->p.k);
    } else {
      *p = (n->left != NULL) ? n->left : n->right;
			void *o = n->p.v;
      free(n);
			return o;
    }
  }
}

bool binary_node_empty(const BinaryNode *n) { return n == NULL; }

KeyValuePair const *binary_node_min(const BinaryNode *root) {
  BinaryNode *n;
  for (n = (BinaryNode *)root; n->left != NULL; n = n->left)
    continue;
  return &(n->p);
}

KeyValuePair const *binary_node_max(const BinaryNode *root) {
  BinaryNode *n;
  for (n = (BinaryNode *)root; n->right != NULL; n = n->right)
    continue;
  return &(n->p);
}

const KeyValuePair *binary_node_predecessor(const BinaryNode *n, Compare c, const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return n->left == NULL ? NULL : binary_node_max(n->left);
  if (r < 0)
    return binary_node_predecessor(n->left, c, k);
  else {
    KeyValuePair const *predecessor = binary_node_predecessor(n->right, c, k);
    return predecessor == NULL ? &(n->p) : predecessor;
  }
}

const KeyValuePair *binary_node_successor(const BinaryNode *n, Compare c, const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return n->right == NULL ? NULL : binary_node_min(n->right);
  if (r > 0)
    return binary_node_successor(n->right, c, k);
  else {
    KeyValuePair const *successor = binary_node_successor(n->left, c, k);
    return successor == NULL ? &(n->p) : successor;
  }
}

void binary_node_pre_order(const BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    v(user_data, n->p.v);
    binary_node_pre_order(n->left, v, user_data);
    binary_node_pre_order(n->right, v, user_data);
  }
}

void binary_node_in_order(const BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    binary_node_in_order(n->left, v, user_data);
    v(user_data, n->p.v);
    binary_node_in_order(n->right, v, user_data);
  }
}

void binary_node_post_order(const BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    binary_node_post_order(n->left, v, user_data);
    binary_node_post_order(n->right, v, user_data);
    v(user_data, n->p.v);
  }
}

void binary_node_level_order(const BinaryNode *root, Visitor v,
                             void *user_data) {
  inline void queue_enqueue_non_null(Queue * q, void * x) {
    if (x != NULL)
      queue_enqueue(q, x);
  }

  Queue *q = linked_queue_new();
  queue_enqueue(q, (BinaryNode *)root);
  while (!container_empty((Container *)q)) {
    BinaryNode *n = queue_dequeue(q);
    v(user_data, n->p.v);
    queue_enqueue_non_null(q, n->left);
    queue_enqueue_non_null(q, n->right);
  }
}
