#include "node.h"

#include <stdlib.h>

Node *node_new(void *x, Node *n) {
  Node *_n = malloc(sizeof(Node));
  _n->x = x;
  _n->n = n;
  return _n;
}

Node *node_new_leaf(void *x) { return node_new(x, NULL); }
