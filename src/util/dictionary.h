#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "container.h"

typedef struct _dictionary_vtable dictionary_vtable;
typedef struct Dictionary {
  dictionary_vtable *vtable;
} Dictionary;
struct _dictionary_vtable {
  container_vtable container;
  void (*insert)(Dictionary *, const void *, void *);
  void *(*reassign)(Dictionary *, const void *, void *);
};

/**
 * Inserts the specified key and value into the dictionary.
 *
 * @param d the dictionary to insert the key value pair into.
 * @param k the key to associate with the value.
 * @param v the value to be indexed by the key.
 */
void dictionary_insert(Dictionary *d, const void *k, void *v);

/**
 * Replaces the value of the specified key with the specified
 * value.
 *
 * @param d the dictionary to replace the value in.
 * @param k the key to associate with the value.
 * @param v the new value that is associated with the key.
 * @return the original value associated with k.
 */
void *dictionary_reassign(Dictionary *d, const void *k, void *v);

/**
 * Deletes the specified key from the dictionary.
 *
 * @param d the dictionary to delete the key from.
 * @param k the key to delete.
 * @return the value associated with the key.
 */
void *dictionary_delete(Dictionary *d, const void *k);

void _container_insert(Container *c, void *k);

#endif /* DICTIONARY_H */
