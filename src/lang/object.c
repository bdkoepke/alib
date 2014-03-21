#include "../diag/contract.h"
#include "object.h"

#include <stdlib.h>

void object_free(Object *o) {
  contract_requires(o != NULL);
  o->vtable->free(o);
}
