#ifndef QUEUE_H
#define QUEUE_H

#include "../object.h"

#include <stdbool.h>

typedef struct _queue_vtable queue_vtable;
typedef struct Queue {
  queue_vtable *vtable;
} Queue;
struct _queue_vtable {
  object_vtable object;
  void (*enqueue)(Queue *, void *);
  void *(*dequeue)(Queue *);
  bool (*empty)(const Queue *);
};

Queue *queue_new();

void queue_enqueue(Queue *, void *);
void *queue_dequeue(Queue *);
bool queue_empty(const Queue *);

void _queue_free(Object *);

#endif /* QUEUE_H */
