#include "hash.h"
#include "type.h"

size_t hash_int_pointer(const void *x) { return (size_t)POINTER_TO_INT(x); }
