#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_node.h"
#include "compare.h"
#include "tree.h"

typedef struct _BinaryTree BinaryTree;

BinaryTree *binary_tree_new(Compare);
BinaryTree *binary_tree_new_fast_min_max(Compare);

BinaryTree *binary_tree_concatenate(BinaryTree *, BinaryTree *);

#endif /* BINARY_TREE_H */
