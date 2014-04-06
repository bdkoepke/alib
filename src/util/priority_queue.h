#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../lang/object.h"
#include "sorted_dictionary.h"

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

/**
 * Creates a new priority queue using the specified dictionary
 * to implement the interface.
 *
 * @param d the dictionary to use.
 * @return a new priority queue backed by the specified dictionary.
 */
PriorityQueue *priority_queue_new(SortedDictionary *d);

/**
 * Inserts the specified object into the priority queue.
 *
 * @param p the priority queue to insert the object into.
 * @param x the object to insert into the priority queue.
 */
void priority_queue_insert(PriorityQueue *p, void *x);

/**
 * Retrieves but does not remove the minimum object from
 * the priority queue.
 *
 * @param p the priority queue to get the minimum object from.
 * @return the minimum object.
 */
void *priority_queue_find_minimum(const PriorityQueue *p);

/**
 * Retrieves but does not remove the maximum object from
 * the priority queue.
 *
 * @param p the priority queue to get the maximum object from.
 * @return the maximum object.
 */
void *priority_queue_find_maximum(const PriorityQueue *p);

/**
 * Removes the minimum object from the priority queue.
 *
 * @param p the queue to retrieve the minimum object from.
 */
void priority_queue_delete_minimum(PriorityQueue *p);

/**
 * Removes the maximum object from the priority queue.
 *
 * @param p the queue to retrieve the maximum object from.
 */
void priority_queue_delete_maximum(PriorityQueue *p);

/**
 * Gets a value indicating whether the priority queue is empty
 * or not.
 *
 * @param p the priority queue to get the emptiness of.
 * @return true if the queue is empty, false otherwise.
 */
bool priority_queue_empty(const PriorityQueue *p);

#endif /* PRIORITY_QUEUE_H */
