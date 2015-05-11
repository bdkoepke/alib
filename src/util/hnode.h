#ifndef HNODE_H
#define HNODE_H

#include "../lang/equals.h"
#include "key_value_pair.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct HNode {
  struct HNode *n;
  KeyValuePair p;
} HNode;

HNode *hnode_new_leaf(const void *k, void *v);
HNode *hnode_new(const void *k, void *v, HNode *n);

bool hnode_empty(const HNode *n);
KeyValuePair *hnode_search(const HNode *n, const void *k, Equals e);
void *hnode_delete(HNode **p, const void *k, Equals e);
void hnode_insert(HNode **p, const void *k, void *v);

void hnode_free_r(HNode *n);

#endif /* HNODE_H */
