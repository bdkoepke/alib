#ifndef HASH_H
#define HASH_H

#include <stddef.h>

typedef size_t (*Hash)(const void *);

extern size_t hash_int_pointer(const void *);

#endif /* HASH_H */
