#ifndef TREE_H
#define TREE_H

#include "../lang/visitor.h"
#include "linked_stack.h"
#include "sorted_dictionary.h"

typedef struct _tree_vtable tree_vtable;
typedef struct Tree {
  tree_vtable *vtable;
} Tree;
struct _tree_vtable {
  sorted_dictionary_vtable sorted_dictionary;
  void (*pre_order)(const Tree *, Visitor, void *);
  void (*in_order)(const Tree *, Visitor, void *);
  void (*post_order)(const Tree *, Visitor, void *);
  void (*level_order)(const Tree *, Visitor, void *);
};

/**
 * Pre order tree traversal.
 *
 * @param t the tree to traverse.
 * @param v the visitor function for the tree.
 * @param user_data the state for the visitor function.
 */
void tree_pre_order(const Tree *t, Visitor v, void *user_data);

/**
 * In order tree traversal.
 *
 * @param t the tree to traverse.
 * @param v the visitor function for the tree.
 * @param user_data the state for the visitor function.
 */
void tree_in_order(const Tree *t, Visitor v, void *user_data);

/**
 * Post order tree traversal.
 *
 * @param t the tree to traverse.
 * @param v the visitor function for the tree.
 * @param user_data the state for the visitor function.
 */
void tree_post_order(const Tree *t, Visitor v, void *user_data);

/**
 * Level order tree traversal.
 *
 * @param t the tree to traverse.
 * @param v the visitor function for the tree.
 * @param user_data the state for the visitor function.
 */
void tree_level_order(const Tree *t, Visitor v, void *user_data);

/**
 * Converts the tree to a sorted linked stack.
 *
 * @param t the tree to get a stack of.
 * @return a new sorted linked stack containing the elements from the tree.
 */
LinkedStack *tree_to_linked_stack(const Tree *t);

#endif /* TREE_H */
