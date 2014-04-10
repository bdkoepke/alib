#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "set.h"

typedef struct _dictionary_vtable dictionary_vtable;
typedef struct Dictionary {
  dictionary_vtable *vtable;
} Dictionary;
struct _dictionary_vtable {
  set_vtable set;
  void *(*search)(const Dictionary *, const void *);
  void (*insert)(Dictionary *, const void *, void *);
  void *(*reassign)(Dictionary *, const void *, void *);
  void *(*delete)(Dictionary *, const void *);
};

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
 * Deletes the object with the specified key from the dictionary.
 *
 * @param d the dictionary to delete the key value pair from.
 * @param k the key to delete from the dictionary.
 * @return a pointer to the value that was deleted.
 */
void *dictionary_delete(Dictionary *d, const void *k);

const void *_dictionary_set_search(const Set *s, const void *x);
void _dictionary_set_insert(Set *s, void *x);
void *_dictionary_set_delete(Set *s, const void *x);

#endif /* DICTIONARY_H */
