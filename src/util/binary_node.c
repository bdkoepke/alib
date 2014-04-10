#include "../diag/contract.h"
#include "binary_node.h"
#include "linked_queue.h"
#include "linked_stack.h"

#include <stdlib.h>

static inline void stack_push_non_null(Stack *s, void *x) {
  if (x != NULL)
    stack_push(s, x);
}

static inline void queue_enqueue_non_null(Queue *q, void *x) {
  if (x != NULL)
    queue_enqueue(q, x);
}

BinaryNode *binary_node_new(const void *k, void *v, BinaryNode *left,
                            BinaryNode *right) {
  BinaryNode *n = malloc(sizeof(BinaryNode));
  n->p.k = k, n->p.v = v;
  n->left = left;
  n->right = right;
  return n;
}

BinaryNode *binary_node_new_leaf(const void *k, void *v) {
  return binary_node_new(k, v, NULL, NULL);
}

bool binary_node_is_leaf(const BinaryNode *n) {
  return n->left == NULL && n->right == NULL;
}

bool binary_node_is_branch(const BinaryNode *n) {
  return n->left != NULL && n->right != NULL;
}

bool binary_node_is_child_of(const BinaryNode *n, const BinaryNode *p) {
  return n == p->left || n == p->right;
}

void binary_node_free_r(BinaryNode *n) {
  if (n != NULL) {
    binary_node_free_r(n->left);
    binary_node_free_r(n->right);
    free(n);
  }
}

void binary_node_insert(BinaryNode *n, BinaryNode **p, Compare c, const void *k,
                        void *v) {
  if (n == NULL)
    *p = binary_node_new_leaf(k, v);
  else {
    p = c(k, n->p.k) < 0 ? &(n->left) : &(n->right);
    binary_node_insert(*p, p, c, k, v);
  }
}

void *binary_node_reassign(BinaryNode *n, Compare c, const void *k, void *v) {
  int r = c(k, n->p.k);
  if (r == 0) {
    void *o = n->p.v;
    n->p.v = v;
    return o;
  } else
    return binary_node_reassign(r < 0 ? n->left : n->right, c, k, v);
}

KeyValuePair const *binary_node_search(const BinaryNode *n, Compare c,
                                       const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return &(n->p);
  return r < 0 ? binary_node_search(n->left, c, k)
               : binary_node_search(n->right, c, k);
}

void *binary_node_delete(BinaryNode *n, BinaryNode **p, Compare c,
                         const void *k) {
  int r = c(k, n->p.k);
  if (r < 0)
    return binary_node_delete(n->left, &(n->left), c, k);
  else if (r > 0)
    return binary_node_delete(n->right, &(n->right), c, k);
  else {
    if (binary_node_is_branch(n)) {
      void *o = n->p.v;
      n->p = *binary_node_min(n->right);
      binary_node_delete(n->right, &(n->right), c, n->p.k);
      return o;
    } else {
      void *o = n->p.v;
      *p = (n->left != NULL) ? n->left : n->right;
      free(n);
      return o;
    }
  }
}

bool binary_node_empty(const BinaryNode *n) { return n == NULL; }

KeyValuePair const *binary_node_min(const BinaryNode *root) {
  BinaryNode *n;
  for (n = (BinaryNode *)root; n->left != NULL; n = n->left)
    continue;
  return &(n->p);
}

KeyValuePair const *binary_node_max(const BinaryNode *root) {
  BinaryNode *n;
  for (n = (BinaryNode *)root; n->right != NULL; n = n->right)
    continue;
  return &(n->p);
}

const KeyValuePair *binary_node_predecessor(const BinaryNode *n, Compare c,
                                            const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return n->left == NULL ? NULL : binary_node_max(n->left);
  if (r < 0)
    return binary_node_predecessor(n->left, c, k);
  else {
    KeyValuePair const *predecessor = binary_node_predecessor(n->right, c, k);
    return predecessor == NULL ? &(n->p) : predecessor;
  }
}

const KeyValuePair *binary_node_successor(const BinaryNode *n, Compare c,
                                          const void *k) {
  if (n == NULL)
    return NULL;
  int r = c(k, n->p.k);
  if (r == 0)
    return n->right == NULL ? NULL : binary_node_min(n->right);
  if (r > 0)
    return binary_node_successor(n->right, c, k);
  else {
    KeyValuePair const *successor = binary_node_successor(n->left, c, k);
    return successor == NULL ? &(n->p) : successor;
  }
}

typedef struct BinaryNodeIterator {
  iterator_vtable *vtable;
  BinaryNode *n;
  Container *c;
} BinaryNodeIterator;

static inline Iterator *binary_node_iterator_new(BinaryNode *root, Container *c,
                                                 iterator_vtable *vtable) {
  BinaryNodeIterator *b = malloc(sizeof(BinaryNodeIterator));
  b->vtable = vtable;
  b->n = root;
  b->c = c;
  return (Iterator *)b;
}

static void binary_node_iterator_free(Object *o) {
  BinaryNodeIterator *b = (BinaryNodeIterator *)o;
  object_free((Object *)b->c);
  free(o);
}

static void *binary_node_current(const Iterator *i) {
  return &(((BinaryNodeIterator *)i)->n)->p;
}

static bool binary_node_move_next_pre_order(Iterator *i) {
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  Container *c = b->c;
  BinaryNode *n = b->n;
  if (n->left != NULL) {
    stack_push_non_null((Stack *)c, n->right);
    return b->n = n->left, true;
  }
  if (n->right != NULL)
    return b->n = n->right, true;
  if (container_empty(c))
    return b->vtable = &iterator_vtable_invalid_state, false;
  return b->n = stack_pop((Stack *)c), true;
}

static bool binary_node_move_next_pre_order_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = binary_node_current, .move_next =
                                            binary_node_move_next_pre_order
  };
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  if (b->n == NULL)
    return b->vtable = &iterator_vtable_invalid_state, false;
  return b->vtable = &vtable, true;
}

Iterator *binary_node_pre_order(BinaryNode *root) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = _iterator_current_invalid_state,
        .move_next = binary_node_move_next_pre_order_init
  };
  return binary_node_iterator_new(root, (Container *)linked_stack_new(),
                                  &vtable);
}

static bool binary_node_move_next_in_order(Iterator *i) {
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  Container *c = b->c;
  BinaryNode *n = b->n;
  for (n = n->right; n != NULL; n = n->left)
    stack_push((Stack *)c, n);
  if (container_empty(c))
    return b->vtable = &iterator_vtable_invalid_state, false;
  return b->n = stack_pop((Stack *)c), true;
}

static bool binary_node_move_next_in_order_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free }, .current = binary_node_current,
                                              .move_next =
                                                  binary_node_move_next_in_order
  };
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  Container *c = b->c;
  BinaryNode *n;
  for (n = b->n; n != NULL; n = n->left)
    stack_push((Stack *)c, n);
  if (container_empty(c))
    return b->vtable = &iterator_vtable_invalid_state, false;
  b->n = stack_pop((Stack *)c);
	return b->vtable = &vtable, true;
}

Iterator *binary_node_in_order(BinaryNode *root) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = _iterator_current_invalid_state,
        .move_next = binary_node_move_next_in_order_init
  };
  return binary_node_iterator_new(root, (Container *)linked_stack_new(),
                                  &vtable);
}

static bool binary_node_move_next_post_order(Iterator *i) {
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  Container *c = b->c;
  if (container_empty(c))
    return b->vtable = &iterator_vtable_invalid_state, false;
  BinaryNode *n = stack_peek((Stack *)c);
  if (binary_node_is_leaf(n) || binary_node_is_child_of(b->n, n))
    return b->n = stack_pop((Stack *)c), true;
  stack_push_non_null((Stack *)c, n->right);
  stack_push_non_null((Stack *)c, n->left);
  return binary_node_move_next_post_order(i);
}

static bool binary_node_move_next_post_order_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = binary_node_current, .move_next =
                                            binary_node_move_next_post_order
  };
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  stack_push_non_null((Stack *)b->c, b->n);
	bool move_next = binary_node_move_next_post_order(i);
	if (move_next)
		b->vtable = &vtable;
	return move_next;
}

Iterator *binary_node_post_order(BinaryNode *root) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = _iterator_current_invalid_state,
        .move_next = binary_node_move_next_post_order_init
  };
  return binary_node_iterator_new(root, (Container *)linked_stack_new(),
                                  &vtable);
}

static bool binary_node_move_next_level_order(Iterator *i) {
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  Container *c = b->c;
  if (container_empty(c))
    return b->vtable = &iterator_vtable_invalid_state, false;
  BinaryNode *n = b->n = queue_dequeue((Queue *)b->c);
  queue_enqueue_non_null((Queue *)c, n->left);
  queue_enqueue_non_null((Queue *)c, n->right);
  return true;
}

static bool binary_node_move_next_level_order_init(Iterator *i) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = binary_node_current, .move_next =
                                            binary_node_move_next_level_order
  };
  BinaryNodeIterator *b = (BinaryNodeIterator *)i;
  BinaryNode *n = b->n;
  Container *c = b->c;
  if (n == NULL)
    return b->vtable = &iterator_vtable_invalid_state, false;
  queue_enqueue_non_null((Queue *)c, n->left);
  queue_enqueue_non_null((Queue *)c, n->right);
  return i->vtable = &vtable, true;
}

Iterator *binary_node_level_order(BinaryNode *root) {
  static iterator_vtable vtable = {
    {.free = binary_node_iterator_free },
        .current = _iterator_current_invalid_state,
        .move_next = binary_node_move_next_level_order_init
  };
  return binary_node_iterator_new(root, (Container *)linked_queue_new(),
                                  &vtable);
}
