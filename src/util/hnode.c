#include "../diag/contract.h"
#include "hnode.h"

#include <assert.h>
#include <stdlib.h>

HNode *hnode_new(const void *k, void *v, HNode *next) {
  HNode *n = malloc(sizeof(HNode));
  n->p.k = k, n->p.v = v;
  n->n = next;
  return n;
}

HNode *hnode_new_leaf(const void *k, void *v) { return hnode_new(k, v, NULL); }

bool hnode_empty(const HNode *n) { return n == NULL; }

KeyValuePair *hnode_search(const HNode *n, const void *k) {
  HNode *_n;
  for (_n = (HNode *)n; _n != NULL; _n = _n->n)
    if (_n->p.k == k)
      return &(_n->p);
  return NULL;
}

void *hnode_delete(HNode **n, const void *k) {
  if ((*n)->p.k != k) {
    HNode *node;
    HNode *next = (*n)->n;
    for (node = *n; next != NULL; node = next) {
      next = node->n;
      if (next->p.k == k) {
        node->n = next->n;
        void *o = next->p.v;
        free(next);
        return o;
      }
    }
  } else {
    HNode *head = *n;
    *n = head->n;
    void *o = head->p.v;
    free(head);
    return o;
  }
}

void hnode_insert(HNode **n, const void *k, void *v) {
  *n = hnode_empty(*n) ? hnode_new_leaf(k, v) : hnode_new(k, v, *n);
}

void hnode_free_r(HNode *n) {
  if (n != NULL) {
    HNode *next;
    for (next = n->n; next != NULL; n = next, next = next->n)
      free(n);
    free(n);
  }
	else puts("node is null");
}
