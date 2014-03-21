#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "compare.h"
#include "linked_stack.h"
#include "tree.h"

#include <stdbool.h>

typedef struct _BinaryTree BinaryTree;

BinaryTree *binary_tree_new(Compare);
BinaryTree *binary_tree_new_fast_min_max(Compare);

BinaryTree *binary_tree_concat(BinaryTree *, BinaryTree *);
bool binary_tree_compare(const BinaryTree *, const BinaryTree *);

#endif /* BINARY_TREE_H */
