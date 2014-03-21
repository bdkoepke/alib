#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
  void *x;
  struct Node *n;
} Node;

Node *node_new_leaf(void *);
Node *node_new(void *, Node *);

bool node_empty(const Node *);
void *node_search(const Node *, const void *);
void node_delete(Node **, const void *);
void node_insert(Node **, void *);
size_t node_middle(const Node *);
int node_loop(const Node *);

void node_free_r(Node *);

#endif /* NODE_H */
