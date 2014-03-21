#include "hash.h"
#include "../type.h"

size_t hash_int_pointer(const void *x) { return POINTER_TO_INT(x); }
