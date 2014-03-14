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
  q->tail = queue_empty(_q) ? (q->head = tail) : (q->tail->n = tail);
}

static void *_queue_dequeue(Queue *_q) {
  _Queue *q = (_Queue *)_q;
  Node *head = q->head;
  q->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

static bool _queue_empty(const Queue *q) { return ((_Queue *)q)->head == NULL; }

Queue *queue_new() {
  static queue_vtable vtable = {
    {.free = _queue_free }, .enqueue = _queue_enqueue,
                                .dequeue = _queue_dequeue, .empty = _queue_empty
  };

  _Queue *q = malloc(sizeof(_Queue));
  q->tail = (q->head = NULL);
  q->vtable = &vtable;
  return (Queue *)q;
}

void queue_enqueue(Queue *q, void *x) {
  contract_requires(q != NULL);
  q->vtable->enqueue(q, x);
  contract_ensures(!queue_empty(q));
}

void *queue_dequeue(Queue *q) {
  contract_requires(q != NULL && !queue_empty(q));
  return q->vtable->dequeue(q);
}

bool queue_empty(const Queue *q) {
  contract_requires(q != NULL);
  return q->vtable->empty(q);
}

void _queue_free(Object *o) {
  Queue *q = (Queue *)o;
  while (!queue_empty(q))
    queue_dequeue(q);
  free(q);
}
