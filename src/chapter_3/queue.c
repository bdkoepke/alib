#include "../contract.h"
#include "node.h"
#include "queue.h"

#include <stdlib.h>

typedef struct {
  queue_vtable *vtable;
  Node *head;
  Node *tail;
} _Queue;

static void _queue_enqueue(Queue *_q, void *x) {
  _Queue *q = (_Queue *)_q;
  Node *tail = node_new_leaf(x);
  q->tail =
      container_empty((Container *)_q) ? (q->head = tail) : (q->tail->n = tail);
}

static void *_queue_dequeue(Queue *_q) {
  _Queue *q = (_Queue *)_q;
  Node *head = q->head;
  q->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

void _queue_insert(Container *c, void *x) { queue_enqueue((Queue *)c, x); }

static bool queue_empty(const Container *c) {
  return ((_Queue *)c)->head == NULL;
}

static void *queue_search(const Container *c, const void *x) {
  const _Queue *q = (const _Queue *)c;
  Node *node;
  for (node = q->head; node != NULL; node = node->n)
    if (node->x == x)
      return node->x;
  return NULL;
}

static void queue_delete(Container *c, const void *x) {
  _Queue *q = (_Queue *)c;
  if (q->head->x != x) {
    Node *node;
    Node *next = q->head->n;
    for (node = q->head; next != NULL; node = next) {
      next = node->n;
      if (next->x == x) {
        node->n = next->n;
        break;
      }
    }
  } else {
    Node *head = q->head;
    q->head = head->n;
    free(head);
  }
}

Queue *queue_new() {
  static queue_vtable vtable = {
    { {.free = _queue_free }, .insert = _queue_insert,
                                  .search = queue_search, .empty = queue_empty,
                                  .delete = queue_delete },
        .enqueue = _queue_enqueue, .dequeue = _queue_dequeue,
  };

  _Queue *q = malloc(sizeof(_Queue));
  q->tail = (q->head = NULL);
  q->vtable = &vtable;
  return (Queue *)q;
}

void queue_enqueue(Queue *q, void *x) {
  contract_requires(q != NULL);
  q->vtable->enqueue(q, x);
  contract_ensures(!container_empty((Container *)q));
}

void *queue_dequeue(Queue *q) {
  contract_requires(q != NULL && !container_empty((Container *)q));
  return q->vtable->dequeue(q);
}

void _queue_free(Object *o) {
  while (!container_empty((Container *)o))
    queue_dequeue((Queue *)o);
  free(o);
}
