#include "../diag/contract.h"
#include "node.h"

#include <assert.h>
#include <stdlib.h>

typedef struct {
  iterator_vtable *vtable;
  Node *n;
} NodeIterator;

static iterator_vtable vtable_invalid_state = {
  {.free = _object_free }, .current = _iterator_current_invalid_state,
                               .move_next = _iterator_move_next_invalid_state
};

static void *node_iterator_current(const Iterator *i) {
  return ((NodeIterator *)i)->n->x;
}

static bool node_iterator_move_next(Iterator *i) {
  NodeIterator *n = (NodeIterator *)i;
  return (n->n = n->n->n) == NULL ? i->vtable = &vtable_invalid_state,
                                    false : true;
}

static bool node_iterator_move_next_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .current = node_iterator_current,
                                 .move_next = node_iterator_move_next
  };
  if (node_iterator_move_next(i)) {
    i->vtable = &vtable;
    return true;
  }
  return false;
}

Iterator *node_iterator(Node *n) {
  static iterator_vtable vtable = {
    {.free = _object_free }, .current = _iterator_current_invalid_state,
                                 .move_next = node_iterator_move_next_init
  };

  NodeIterator *i = malloc(sizeof(NodeIterator));
  i->vtable = n == NULL ? &vtable_invalid_state : &vtable;
  i->n = n;
  return (Iterator *)i;
}

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

void *node_delete(Node **n, const void *x) {
  if ((*n)->x != x) {
    Node *node;
    Node *next = (*n)->n;
    for (node = *n; next != NULL; node = next) {
      next = node->n;
      if (next->x == x) {
        node->n = next->n;
        void *o = next->x;
        free(next);
        return o;
      }
    }
  } else {
    Node *head = *n;
    *n = head->n;
    void *o = head->x;
    free(head);
    return o;
  }
}

void node_insert(Node **n, void *x) {
  *n = node_empty(*n) ? node_new_leaf(x) : node_new(x, *n);
}

void node_free_r(Node *n) {
  for (; n != NULL; n = n->n)
    free(n);
}

size_t node_middle(const Node *n) {
  Node *slow = (Node *)n;
  Node *fast;
  size_t i = 0;
  for (fast = (Node *)n; fast->n != NULL && fast->n->n != NULL;
       fast = fast->n->n) {
    slow = slow->n;
    i++;
  }
  return i + 1;
}

int node_loop(const Node *n) {
  if (n == NULL || n->n == NULL)
    return -1;
  if (n == n->n || n == n->n->n)
    return 0;
  if (n->n == n->n->n)
    return 1;
  Node *slow = (Node *)n;
  Node *fast;
  int i = 0;
  for (fast = (Node *)n->n->n; fast->n != NULL && fast->n->n != NULL;
       fast = fast->n->n) {
    if (slow == fast)
      return i;
    slow = slow->n;
    i++;
  }
  return -1;
}
