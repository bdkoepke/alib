#include "../diag/contract.h"
#include "binary_node.h"
#include "queue.h"

#include <stdlib.h>

BinaryNode *binary_node_new(void *x, BinaryNode *left, BinaryNode *right) {
  BinaryNode *_n = malloc(sizeof(BinaryNode));
  _n->x = x;
  _n->left = left;
  _n->right = right;
  return _n;
}

BinaryNode *binary_node_new_leaf(void *x) {
  return binary_node_new(x, NULL, NULL);
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

void binary_node_insert(BinaryNode *n, BinaryNode **p, Compare c, void *x) {
  if (n == NULL)
    *p = binary_node_new_leaf(x);
  else {
    int r = c(x, n->x);
    BinaryNode **_p = r < 0 ? &(n->left) : &(n->right);
    binary_node_insert(*_p, _p, c, x);
  }
}

void *binary_node_search(const BinaryNode *n, Compare c, const void *x) {
  if (n == NULL)
    return NULL;
  int r = c(x, n->x);
  if (r == 0)
    return n->x;
  return r < 0 ? binary_node_search(n->left, c, x)
               : binary_node_search(n->right, c, x);
}

void binary_node_delete(BinaryNode *n, BinaryNode **p, Compare c,
                        const void *x) {
  int r = c(x, n->x);
  if (r < 0)
    binary_node_delete(n->left, &(n->left), c, x);
  else if (r > 0)
    binary_node_delete(n->right, &(n->right), c, x);
  else {
    if (binary_node_is_branch(n)) {
      void *min = binary_node_min(n->right);
      n->x = min;
      binary_node_delete(n->right, &(n->right), c, min);
    } else {
      *p = (n->left != NULL) ? n->left : n->right;
      free(n);
    }
  }
}

bool binary_node_empty(const BinaryNode *n) { return n == NULL; }

void *binary_node_min(BinaryNode *root) {
  BinaryNode *n;
  for (n = root; n->left != NULL; n = n->left)
    continue;
  return n->x;
}

void *binary_node_max(BinaryNode *root) {
  BinaryNode *n;
  for (n = root; n->right != NULL; n = n->right)
    continue;
  return n->x;
}

void *binary_node_predecessor(const BinaryNode *n, Compare c, const void *x) {
  if (n == NULL)
    return NULL;
  int r = c(x, n->x);
  if (r == 0)
    return n->left == NULL ? NULL : binary_node_max(n->left);
  if (r < 0)
    return binary_node_predecessor(n->left, c, x);
  else {
    void *predecessor = binary_node_predecessor(n->right, c, x);
    return predecessor == NULL ? n->x : predecessor;
  }
}

void *binary_node_successor(const BinaryNode *n, Compare c, const void *x) {
  if (n == NULL)
    return NULL;
  int r = c(x, n->x);
  if (r == 0)
    return n->right == NULL ? NULL : binary_node_min(n->right);
  if (r > 0)
    return binary_node_successor(n->right, c, x);
  else {
    void *successor = binary_node_successor(n->left, c, x);
    return successor == NULL ? n->x : successor;
  }
}

void binary_node_pre_order(BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    v(user_data, n->x);
    binary_node_pre_order(n->left, v, user_data);
    binary_node_pre_order(n->right, v, user_data);
  }
}

void binary_node_in_order(BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    binary_node_in_order(n->left, v, user_data);
    v(user_data, n->x);
    binary_node_in_order(n->right, v, user_data);
  }
}

void binary_node_post_order(BinaryNode *n, Visitor v, void *user_data) {
  if (n != NULL) {
    binary_node_post_order(n->left, v, user_data);
    binary_node_post_order(n->right, v, user_data);
    v(user_data, n->x);
  }
}

static void queue_enqueue_non_null(Queue *q, void *x) {
  if (x != NULL)
    queue_enqueue(q, x);
}

void binary_node_level_order(BinaryNode *root, Visitor v, void *user_data) {
  Queue *q = queue_new();
  queue_enqueue(q, root);
  while (!container_empty((Container *)q)) {
    BinaryNode *n = queue_dequeue(q);
    v(user_data, n->x);
    queue_enqueue_non_null(q, n->left);
    queue_enqueue_non_null(q, n->right);
  }
}
