#ifndef TUPLE_H
#define TUPLE_H

typedef struct {
  void *first;
  void *second;
} Tuple;

Tuple *tuple_new(void *, void *);

#endif /* TUPLE_H */
