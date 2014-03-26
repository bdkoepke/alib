#ifndef TUPLE_H
#define TUPLE_H

typedef struct {
  void *first;
  void *second;
} Tuple;

/**
 * Creates a new tuple.
 *
 * @param first the first value in the tuple.
 * @param second the second value in the tuple.
 * @return a new tuple containing the specified first and second values.
 */
Tuple *tuple_new(void *first, void *second);

#endif /* TUPLE_H */
