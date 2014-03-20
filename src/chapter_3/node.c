#include "../contract.h"
#include "node.h"

#include <assert.h>
#include <stdlib.h>

Node *node_new(void *x, Node *n) {
  Node *_n = malloc(sizeof(Node));
  _n->x = x;
  _n->n = n;
  return _n;
}

Node *node_new_leaf(void *x) { return node_new(x, NULL); }

bool node_empty(const Node *n) { return n == NULL; }

void *node_search(const Node *n, const void *x) {
  Node *_n;
  for (_n = (Node *)n; _n != NULL; _n = _n->n)
    if (_n->x == x)
      return _n->x;
  return NULL;
}

void node_delete(Node **n, const void *x) {
  if ((*n)->x != x) {
    Node *node;
    Node *next = (*n)->n;
    for (node = *n; next != NULL; node = next) {
      next = node->n;
      if (next->x == x) {
        node->n = next->n;
        return;
      }
    }
  } else {
    Node *head = *n;
    *n = head->n;
    free(head);
  }
}

void node_insert(Node **n, void *x) {
  *n = node_empty(*n) ? node_new_leaf(x) : node_new(x, *n);
}

void node_free_r(Node *n) {
  for (; n != NULL; n = n->n)
    free(n);
}
