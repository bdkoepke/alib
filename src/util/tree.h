#ifndef TREE_H
#define TREE_H

#include "linked_stack.h"
#include "sorted_dictionary.h"

typedef struct _tree_vtable tree_vtable;
typedef struct Tree {
  tree_vtable *vtable;
} Tree;
struct _tree_vtable {
  sorted_dictionary_vtable sorted_dictionary;
  Iterator *(*pre_order)(const Tree *);
  Iterator *(*in_order)(const Tree *);
  Iterator *(*post_order)(const Tree *);
  Iterator *(*level_order)(const Tree *);
};

/**
 * Pre order tree traversal.
 *
 * @param t the tree to traverse
 * @return a pre order iterator for the tree.
 */
Iterator *tree_pre_order(const Tree *t);

/**
 * In order tree traversal.
 *
 * @param t the tree to traverse
 * @return an in order iterator for the tree.
 */
Iterator *tree_in_order(const Tree *t);

/**
 * Post order tree traversal.
 *
 * @param t the tree to traverse
 * @return post post order iterator for the tree.
 */
Iterator *tree_post_order(const Tree *t);

/**
 * Level order tree traversal.
 *
 * @param t the tree to traverse
 * @return a level order iterator for the tree.
 */
Iterator *tree_level_order(const Tree *t);

/**
 * Converts the tree to a sorted linked stack.
 *
 * @param t the tree to get a stack of.
 * @return a new sorted linked stack containing the elements from the tree.
 */
LinkedStack *tree_to_linked_stack(const Tree *t);

#endif /* TREE_H */
