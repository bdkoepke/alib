#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "compare.h"
#include "key_value_pair.h"
#include "iterator.h"

#include <stdbool.h>

typedef struct BinaryNode {
  KeyValuePair p;
  struct BinaryNode *left;
  struct BinaryNode *right;
} BinaryNode;

BinaryNode *binary_node_new_leaf(const void *k, void *v);
BinaryNode *binary_node_new(const void *k, void *v, BinaryNode *left,
                            BinaryNode *right);
bool binary_node_is_leaf(const BinaryNode *);
bool binary_node_is_branch(const BinaryNode *);
bool binary_node_is_child_of(const BinaryNode *, const BinaryNode *);

void binary_node_free_r(BinaryNode *);

const KeyValuePair *binary_node_search(const BinaryNode *, Compare,
                                       const void *k);
void *binary_node_delete(BinaryNode *, BinaryNode **root, Compare,
                         const void *k);
bool binary_node_empty(const BinaryNode *);

void binary_node_insert(BinaryNode *, BinaryNode **root, Compare, const void *k,
                        void *v);
void *binary_node_reassign(BinaryNode *, Compare, const void *k, void *v);

const KeyValuePair *binary_node_min(const BinaryNode *);
const KeyValuePair *binary_node_max(const BinaryNode *);
const KeyValuePair *binary_node_predecessor(const BinaryNode *, Compare,
                                            const void *k);
const KeyValuePair *binary_node_successor(const BinaryNode *, Compare,
                                          const void *k);

Iterator *binary_node_pre_order(BinaryNode *);
Iterator *binary_node_in_order(BinaryNode *);
Iterator *binary_node_post_order(BinaryNode *);
Iterator *binary_node_level_order(BinaryNode *);

#endif /* BINARY_NODE_H */
