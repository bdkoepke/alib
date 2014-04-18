#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../lang/compare.h"
#include "linked_stack.h"
#include "tree.h"

#include <stdbool.h>

typedef struct {
  tree_vtable *vtable;
} BinaryTree;

/**
 * Creates a new binary tree with the specified comparison function.
 * 
 * @param c the comparison function.
 * @return a new binary tree.
 */
BinaryTree *binary_tree_new(Compare c);

/**
 * Creates a new binary tree that caches the current min and max values.
 *
 * @param c the comparison function.
 * @return a new binary tree.
 */
BinaryTree *binary_tree_new_fast_min_max(Compare);

/**
 * Concats two binary trees, invalidating both and then returns the
 * remaining valid tree.
 *
 * @param a the first binary tree.
 * @param b the second binary tree.
 * @return the resulting combined tree pointer.
 */
BinaryTree *binary_tree_concat(BinaryTree *a, BinaryTree *b);

/**
 * Compares two binary trees for equality.
 *
 * @param a the first binary tree.
 * @param b the second binary tree.
 * @return true if the trees are equal, false otherwise.
 */
bool binary_tree_compare(const BinaryTree *a, const BinaryTree *b);

#endif /* BINARY_TREE_H */
