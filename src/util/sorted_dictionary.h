#ifndef SORTED_DICTIONARY_H
#define SORTED_DICTIONARY_H

#include "dictionary.h"

typedef struct _sorted_dictionary_vtable sorted_dictionary_vtable;
typedef struct SortedDictionary {
  sorted_dictionary_vtable *vtable;
} SortedDictionary;
struct _sorted_dictionary_vtable {
  dictionary_vtable dictionary;
  void *(*max)(const SortedDictionary *);
  void *(*min)(const SortedDictionary *);
  void *(*predecessor)(const SortedDictionary *, const void *);
  void *(*successor)(const SortedDictionary *, const void *);
};

/**
 * Gets the maximum object from the dictionary.
 *
 * @param d the dictionary to get the maximum from.
 * @return the maximum object.
 */
void *sorted_dictionary_max(const SortedDictionary *d);

/**
 * Gets the minimum object from the dictionary.
 *
 * @param d the dictionary to get the minimum from.
 * @return the minimum object.
 */
void *sorted_dictionary_min(const SortedDictionary *d);

/**
 * Gets the predecessor of the specified object from the dictionary.
 *
 * @param d the dictionary to get the predecessor of.
 * @param x the largest object that is less than x.
 * @return the predecessor if it exists, NULL otherwise.
 */
void *sorted_dictionary_predecessor(const SortedDictionary *d, const void *k);

/**
 * Gets the successor of the specified object from the dictionary.
 *
 * @param d the dictionary to get the successor of.
 * @param x the smallest object that is greater than x.
 * @return the successor if it exists, NULL otherwise.
 */
void *sorted_dictionary_successor(const SortedDictionary *d, const void *k);

#endif /* SORTED_DICTIONARY_H */
