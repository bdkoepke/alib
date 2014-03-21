#include "../diag/contract.h"
#include "binary_node.h"
#include "red_black_tree.h"

#include <assert.h>
#include <stdlib.h>

typedef enum Color {
  Red,
  Black
} Color;

typedef struct RedBlackNode {
  void *x;
  struct RedBlackNode *left;
  struct RedBlackNode *right;
  Color c;
} RedBlackNode;

RedBlackNode *red_black_node_new(void *x, Color c, RedBlackNode *left,
                                 RedBlackNode *right) {
  RedBlackNode *r = malloc(sizeof(RedBlackNode));
  r->x = x;
  r->c = c;
  r->left = left;
  r->right = right;
  return r;
}

RedBlackNode *red_black_node_new_leaf(void *x, Color c) {
  return red_black_node_new(x, c, NULL, NULL);
}

typedef struct {
  tree_vtable *vtable;
  RedBlackNode *root;
  Compare c;
} RedBlackTree;

Tree *red_black_tree_new(Compare c) {
  /* static tree_vtable vtable = {
    { { {.free = binary_tree_free },
            .search = binary_tree_search, .insert = binary_tree_insert,
            .delete = binary_tree_delete, .empty = binary_tree_empty },
          .max = binary_tree_max, .min = binary_tree_min,
          .predecessor = binary_tree_predecessor, .successor =
                                                      binary_tree_successor },
        .pre_order = binary_tree_pre_order, .in_order = binary_tree_in_order,
        .post_order = binary_tree_post_order, .level_order =
                                                  binary_tree_level_order
  }; */

  contract_requires(c != NULL);

  RedBlackTree *r = malloc(sizeof(RedBlackTree));
  //r->vtable = &vtable;
  r->root = NULL;
  r->c = c;
  return (Tree *)r;
}
