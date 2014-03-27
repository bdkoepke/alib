#ifndef OBJECT_H
#define OBJECT_H

typedef struct _object_vtable object_vtable;
typedef struct {
  object_vtable *vtable;
} Object;
struct _object_vtable {
  void (*free)(Object *);
};

/**
 * Frees the memory used by the specified object.
 *
 * @param o the object to free.
 */
void object_free(Object *o);

/**
 * Default implementation of object_free for simple
 * objects that don't require additional resource
 * management.
 *
 * @param o the object to free.
 */
void _object_free(Object *o);

#endif /* OBJECT_H */
