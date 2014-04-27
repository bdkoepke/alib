#include "../diag/contract.h"
#include "priority_queue.h"

#include <stdlib.h>

typedef struct {
  priority_queue_vtable *vtable;
  SortedDictionary *dictionary;
} _PriorityQueue;

void _priority_queue_insert(PriorityQueue *p, void *x) {
  container_insert((Container *)((_PriorityQueue *)p)->dictionary, x);
}

void *_priority_queue_find_minimum(const PriorityQueue *p) {
  return sorted_dictionary_min(((_PriorityQueue *)p)->dictionary);
}

void *_priority_queue_find_maximum(const PriorityQueue *p) {
  return sorted_dictionary_max(((_PriorityQueue *)p)->dictionary);
}

void _priority_queue_delete_minimum(PriorityQueue *p) {
  container_delete((Container *)((_PriorityQueue *)p)->dictionary,
                   priority_queue_find_minimum(p));
}

void _priority_queue_delete_maximum(PriorityQueue *p) {
  container_delete((Container *)((_PriorityQueue *)p)->dictionary,
                   priority_queue_find_maximum(p));
}

bool _priority_queue_empty(const PriorityQueue *p) {
  return container_empty((Container *)((_PriorityQueue *)p)->dictionary);
}

void _priority_queue_free(Object *o) {
  object_free((Object *)((_PriorityQueue *)o)->dictionary);
  free(o);
}

PriorityQueue *priority_queue_new(SortedDictionary *dictionary) {
  static priority_queue_vtable vtable = {
    { .class = "priority_queue",
      .free = _priority_queue_free,
      .to_string = _object_to_string },
    .insert = _priority_queue_insert,
    .find_minimum = _priority_queue_find_minimum,
    .find_maximum = _priority_queue_find_maximum,
    .delete_minimum = _priority_queue_delete_minimum,
    .delete_maximum = _priority_queue_delete_maximum,
    .empty = _priority_queue_empty
  };

  _PriorityQueue *p = malloc(sizeof(_PriorityQueue));
  p->dictionary = dictionary;
  p->vtable = &vtable;
  return (PriorityQueue *)p;
}

void priority_queue_insert(PriorityQueue *p, void *x) {
  p->vtable->insert(contract_requires_non_null(p), x);
  contract_ensures(!priority_queue_empty(p));
}

void *priority_queue_find_minimum(const PriorityQueue *p) {
  contract_requires(!priority_queue_empty(p));
  return p->vtable->find_minimum(contract_requires_non_null(p));
}

void *priority_queue_find_maximum(const PriorityQueue *p) {
  contract_requires(!priority_queue_empty(p));
  return p->vtable->find_maximum(contract_requires_non_null(p));
}

void priority_queue_delete_minimum(PriorityQueue *p) {
  contract_requires(!priority_queue_empty(p));
  p->vtable->delete_minimum(contract_requires_non_null(p));
}

void priority_queue_delete_maximum(PriorityQueue *p) {
  contract_requires(!priority_queue_empty(p));
  p->vtable->delete_maximum(contract_requires_non_null(p));
}

bool priority_queue_empty(const PriorityQueue *p) {
  return p->vtable->empty(contract_requires_non_null(p));
}
