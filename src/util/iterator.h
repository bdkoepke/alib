#ifndef ITERATOR_H
#define ITERATOR_H

#include "../lang/object.h"

#include <stdbool.h>

typedef struct _iterator_vtable iterator_vtable;
typedef struct Iterator {
  iterator_vtable *vtable;
} Iterator;
struct _iterator_vtable {
  object_vtable object;
  void *(*current)(const Iterator *);
  bool (*move_next)(Iterator *);
};

/**
 * Gets the current iterator object.
 *
 * @param i the iterator.
 * @return the current iterator object.
 */
void *iterator_current(const Iterator *i);

/**
 * Moves the iterator to the next object.
 *
 * @param i the iterator to advance.
 * @return true if the iterator moved to
 *      the next object, false otherwise.
 */
bool iterator_move_next(Iterator *i);

typedef void (*apply)(void *user_data, void *x);
void iterator_foreach(Iterator *i, apply a, void *user_data);

void *_iterator_current_invalid_state(const Iterator *i);
bool _iterator_move_next_invalid_state(Iterator *i);

#endif /* ITERATOR_H */
