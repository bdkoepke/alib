#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "set.h"

typedef struct _dictionary_vtable dictionary_vtable;
typedef struct Dictionary {
  dictionary_vtable *vtable;
} Dictionary;
struct _dictionary_vtable {
  object_vtable object;
  const Set *(*values)(const Dictionary *);
  const Set *(*keys)(const Dictionary *);
  void *(*search)(const Dictionary *, const void *);
  void (*insert)(Dictionary *, const void *, void *);
  void *(*reassign)(Dictionary *, const void *, void *);
  void *(*delete)(Dictionary *, const void *);
  bool (*empty)(const Dictionary *);
};

/**
 * Gets a read only set containing the dictionary values.
 *
 * @param d the dictionary to get a set view.
 * @return a set view containing the values in the dictionary.
 */
const Set *dictionary_values(const Dictionary *d);

/**
 * Gets a read only set containing the dictionary keys.
 *
 * @param d the dictionary to get a set view.
 * @return a set view containing the keys in the dictionary.
 */
const Set *dictionary_keys(const Dictionary *d);

/**
 * Searches the specified dictionary for the specified item.
 *
 * @param d the dictionary to search.
 * @param k the key to search for.
 * @return the value v from the dictionary associated with the
 * 	key k if it exists, NULL otherwise.
 */
void *dictionary_search(const Dictionary *d, const void *k);

/**
 * Inserts the specified key and value into the dictionary.
 * *
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
 * Gets a value indicating whether the dictionary is empty or not.
 *
 * @param d the dictionary to check for emptiness.
 * @return true if the dictionary is empty, false otherwise.
 */
bool dictionary_empty(const Dictionary *d);

/**
 * Deletes the object with the specified key from the dictionary.
 *
 * @param d the dictionary to delete the key value pair from.
 * @param k the key to delete from the dictionary.
 * @return a pointer to the value that was deleted.
 */
void *dictionary_delete(Dictionary *c, const void *k);

/**
 * Creates a set using the specified dictionary as a backend.
 *
 * @param d an empty dictionary to use as the backend.
 * @return a set backed by the specified dictionary.
 */
Set *set_from_dictionary(Dictionary *d);

#endif /* DICTIONARY_H */
