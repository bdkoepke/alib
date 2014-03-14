#ifndef NODE_H
#define NODE_H

typedef struct Node {
  void *x;
  struct Node *n;
} Node;

Node *node_new_leaf(void *);
Node *node_new(void *, Node *);

void node_insert(Node *, void *);

#endif /* NODE_H */
