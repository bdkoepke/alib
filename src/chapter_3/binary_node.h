#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "../compare.h"
#include "visitor.h"

#include <stdbool.h>

typedef struct BinaryNode {
  void *x;
  struct BinaryNode *left;
  struct BinaryNode *right;
} BinaryNode;

BinaryNode *binary_node_new_leaf(void *);
BinaryNode *binary_node_new(void *, BinaryNode *, BinaryNode *);
bool binary_node_is_leaf(const BinaryNode *);
bool binary_node_is_branch(const BinaryNode *);

void binary_node_free_r(BinaryNode *);

void binary_node_insert(BinaryNode *, BinaryNode **, Compare, void *);
void *binary_node_search(const BinaryNode *, Compare, const void *);
void binary_node_delete(BinaryNode *, BinaryNode **, Compare, const void *);
bool binary_node_empty(const BinaryNode *);

void *binary_node_min(BinaryNode *);
void *binary_node_max(BinaryNode *);
void *binary_node_predecessor(const BinaryNode *, Compare, const void *);
void *binary_node_successor(const BinaryNode *, Compare, const void *);

void binary_node_pre_order(BinaryNode *, Visitor, void *);
void binary_node_in_order(BinaryNode *, Visitor, void *);
void binary_node_post_order(BinaryNode *, Visitor, void *);
void binary_node_level_order(BinaryNode *, Visitor, void *);

#endif /* BINARY_NODE_H */
