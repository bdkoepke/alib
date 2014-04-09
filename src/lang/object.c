#include "../diag/contract.h"
#include "object.h"

#include <stdlib.h>

void _object_free(Object *o) { free(o); }

void object_free(Object *o) { o->vtable->free(contract_requires_non_null(o)); }
