#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../lang/equals.h"
#include "../lang/hash.h"
#include "dictionary.h"

/**
 * Creates a new hash table.
 *
 * @param hash the hash function for the objects.
 * @return a new hashtable.
 */
Dictionary *hashtable_new(Hash, Equals);

#endif /* HASHTABLE_H */
