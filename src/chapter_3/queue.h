#ifndef QUEUE_H
#define QUEUE_H

#include "container.h"

typedef struct _queue_vtable queue_vtable;
typedef struct Queue {
  queue_vtable *vtable;
} Queue;
struct _queue_vtable {
	container_vtable container;
  void (*enqueue)(Queue *, void *);
  void *(*dequeue)(Queue *);
};

Queue *queue_new();

void queue_enqueue(Queue *, void *);
void *queue_dequeue(Queue *);

void _queue_insert(Container *, void *);

void _queue_free(Object *);

#endif /* QUEUE_H */
