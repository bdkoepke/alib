#include "binary_node.h"

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
