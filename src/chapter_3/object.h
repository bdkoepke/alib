#ifndef OBJECT_H
#define OBJECT_H

typedef struct _object_vtable object_vtable;
typedef struct {
  object_vtable *vtable;
} Object;
struct _object_vtable {
  void (*free)(Object *);
};

void object_free(Object *);

#endif /* OBJECT_H */
