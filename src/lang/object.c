#include "../diag/contract.h"
#include "object.h"

#include <stdlib.h>

void _object_free(Object *o) { free(o); }

void object_free(Object *o) {
  contract_requires(o != NULL);
  o->vtable->free(o);
}
