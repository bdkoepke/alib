#ifndef HASH_H
#define HASH_H

#include <stddef.h>

/**
 * Template for hash function.
 */
typedef size_t (*Hash)(const void *x);

/**
 * Uses the objects pointer as it's hash function.
 */
extern size_t hash_int_pointer(const void *x);

#endif /* HASH_H */
