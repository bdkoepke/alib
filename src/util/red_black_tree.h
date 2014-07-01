#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../lang/compare.h"
#include "tree.h"

/**
 * Creates a new red black tree.
 *
 * @param c the comparison function for the tree.
 * @return a new red black tree.
 */
Tree *red_black_tree_new(Compare c);

#endif /* RED_BLACK_TREE_H */
