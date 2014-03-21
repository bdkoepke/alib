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
  void *(*current)(Iterator *);
  bool (*move_next)(Iterator *);
};

void *iterator_current(Iterator *);
bool iterator_move_next(Iterator *);

#endif /* ITERATOR_H */
