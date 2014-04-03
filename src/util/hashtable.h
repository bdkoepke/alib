#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../lang/hash.h"
#include "container.h"

/**
 * Creates a new hash table.
 *
 * @param hash the hash function for the objects.
 * @return a new hashtable.
 */
Container *hashtable_new(Hash);

#endif /* HASHTABLE_H */
