#ifndef BINARY_NODE_H
#define BINARY_NODE_H

typedef struct BinaryNode {
  void *x;
  struct BinaryNode *left;
  struct BinaryNode *right;
} BinaryNode;

BinaryNode *binary_node_new_leaf(void *);
BinaryNode *binary_node_new(void *, BinaryNode *, BinaryNode *);

#endif /* BINARY_NODE_H */
