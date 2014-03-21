#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "compare.h"
#include "tree.h"

typedef struct _BinaryTree BinaryTree;

BinaryTree *binary_tree_new(Compare);
BinaryTree *binary_tree_new_fast_min_max(Compare);

BinaryTree *binary_tree_concat(BinaryTree *, BinaryTree *);

#endif /* BINARY_TREE_H */
