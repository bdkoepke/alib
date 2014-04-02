#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../lang/hash.h"
#include "mutable_container.h"

/**
 * Creates a new hash table.
 *
 * @param hash the hash function for the objects.
 * @return a new hashtable.
 */
MutableContainer *hashtable_new(Hash);

#endif /* HASHTABLE_H */
