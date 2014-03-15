#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_node.h"
#include "compare.h"
#include "tree.h"

typedef struct {
  tree_vtable *vtable;
  BinaryNode *root;
  Compare c;
} BinaryTree;

BinaryTree *binary_tree_new(Compare);

#endif /* BINARY_TREE_H */
