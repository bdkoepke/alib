#include "../diag/contract.h"
#include "node.h"
#include "queue.h"

#include <stdlib.h>

void queue_enqueue(Queue *q, void *x) {
  contract_requires(q != NULL);
  q->vtable->enqueue(q, x);
  contract_ensures(!container_empty((Container *)q));
}

void *queue_dequeue(Queue *q) {
  contract_requires(q != NULL && !container_empty((Container *)q));
  return q->vtable->dequeue(q);
}

void *queue_head(const Queue *q) {
  contract_requires(q != NULL && !container_empty((Container *)q));
  return q->vtable->head(q);
}

void _queue_insert(Container *c, void *x) {
  queue_enqueue((Queue *)c, x);
}

void _queue_free(Object *o) {
  while (!container_empty((Container *)o))
    queue_dequeue((Queue *)o);
  free(o);
}
