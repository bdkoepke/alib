#ifndef OBJECT_H
#define OBJECT_H

#include "class.h"

typedef struct _object_vtable object_vtable;
typedef struct {
  object_vtable *vtable;
} Object;
struct _object_vtable {
  const Class *(*class)(const Object *);
  void (*free)(Object *);
  char *(*to_string)(const Object *);
};

/**
 * Gets a reference to the objects class object.
 *
 * @param o the object to get the class of.
 * @return a reference to the objects class object.
 */
const Class *object_class(const Object *o);

/**
 * Frees the memory used by the specified object.
 *
 * @param o the object to free.
 */
void object_free(Object *o);

/**
 * Gets a string representation of the specified object.
 *
 * @param o the object to get the string representation of.
 * @return a string representation of the object.
 */
char *object_to_string(const Object *o);

void _object_free(Object *o);
char *_object_to_string(const Object *o);

#endif /* OBJECT_H */
