#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../object.h"

#include <stdbool.h>

typedef struct _priority_queue_vtable priority_queue_vtable;
typedef struct PriorityQueue {
  priority_queue_vtable *vtable;
} PriorityQueue;
struct _priority_queue_vtable {
  object_vtable object;
  void (*insert)(PriorityQueue *, void *);
  void *(*find_minimum)(const PriorityQueue *);
  void *(*find_maximum)(const PriorityQueue *);
  void (*delete_minimum)(PriorityQueue *);
  void (*delete_maximum)(PriorityQueue *);
  bool (*empty)(const PriorityQueue *);
};

PriorityQueue *priority_queue_new(Dictionary *);

void priority_queue_insert(PriorityQueue *, void *);
void *priority_queue_find_minimum(const PriorityQueue *);
void *priority_queue_find_maximum(const PriorityQueue *);
void priority_queue_delete_minimum(PriorityQueue *);
void priority_queue_delete_maximum(PriorityQueue *);
bool priority_queue_empty(const PriorityQueue *);

#endif /* PRIORITY_QUEUE_H */
