#include "../diag/contract.h"
#include "linked_queue.h"
#include "node.h"
#include "queue.h"

#include <stdlib.h>

typedef struct {
  queue_vtable *vtable;
  Node *head;
  Node *tail;
} LinkedQueue;

static void linked_queue_enqueue(Queue *_q, void *x) {
  LinkedQueue *q = (LinkedQueue *)_q;
  Node *tail = node_new_leaf(x);
  q->tail =
      container_empty((Container *)_q) ? (q->head = tail) : (q->tail->n = tail);
}

static void *linked_queue_dequeue(Queue *_q) {
  LinkedQueue *q = (LinkedQueue *)_q;
  Node *head = q->head;
  q->head = head->n;
  void *x = head->x;
  free(head);
  return x;
}

static void *linked_queue_head(const Queue *q) {
  return ((const LinkedQueue *)q)->head->x;
}

static bool linked_queue_empty(const Container *c) {
  return node_empty(((LinkedQueue *)c)->head);
}

static void *linked_queue_search(const Container *c, const void *x) {
  return node_search(((const LinkedQueue *)c)->head, x);
}

static void *linked_queue_delete(Container *c, const void *x) {
  LinkedQueue *q = (LinkedQueue *)c;
  if (q->head->x != x) {
    Node *node;
    Node *next = q->head->n;
    for (node = q->head; next != NULL; node = next) {
      next = node->n;
      if (next->x == x) {
        node->n = next->n;
        if (node->n == NULL)
          q->tail = node;
				void *o = next->x;
				free(next);
        return o;
      }
    }
  } else {
    Node *head = q->head;
    q->head = head->n;
    free(head);
  }
}

Queue *linked_queue_new() {
  static queue_vtable vtable = {
    { { {.free = _queue_free }, .iterator = NULL },
          .empty = linked_queue_empty, .search = linked_queue_search,
          .insert = _queue_insert, .delete = linked_queue_delete },
        .enqueue = linked_queue_enqueue, .dequeue = linked_queue_dequeue,
        .head = linked_queue_head
  };

  LinkedQueue *q = malloc(sizeof(LinkedQueue));
  q->tail = (q->head = NULL);
  q->vtable = &vtable;
  return (Queue *)q;
}
