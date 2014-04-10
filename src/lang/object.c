#include "../diag/contract.h"
#include "object.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _object_free(Object *o) { free(o); }

void object_free(Object *o) { o->vtable->free(contract_requires_non_null(o)); }

const Class *object_class(const Object *o) {
  return o->vtable->class(contract_requires_non_null(o));
}

char *object_to_string(const Object *o) {
  return o->vtable->to_string(contract_requires_non_null(o));
}

char *_object_to_string(const Object *o) {
  const char *name = class_name(object_class(o));
  size_t size = sizeof(void *) + sizeof('@') + strlen(name) + sizeof('\n');
  char *buffer = malloc(size);
  snprintf(buffer, size, "%s@%x", name, o);
  return buffer;
}
