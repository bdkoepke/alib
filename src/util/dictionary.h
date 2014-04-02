#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "mutable_container.h"

typedef struct _dictionary_vtable dictionary_vtable;
typedef struct Dictionary {
  dictionary_vtable *vtable;
} Dictionary;
struct _dictionary_vtable {
  mutable_container_vtable container;
  void *(*max)(const Dictionary *);
  void *(*min)(const Dictionary *);
  void *(*predecessor)(const Dictionary *, const void *);
  void *(*successor)(const Dictionary *, const void *);
};

/**
 * Gets the maximum object from the dictionary.
 *
 * @param d the dictionary to get the maximum from.
 * @return the maximum object.
 */
void *dictionary_max(const Dictionary *d);

/**
 * Gets the minimum object from the dictionary.
 *
 * @param d the dictionary to get the minimum from.
 * @return the minimum object.
 */
void *dictionary_min(const Dictionary *d);

/**
 * Gets the predecessor of the specified object from the dictionary.
 *
 * @param d the dictionary to get the predecessor of.
 * @param x the largest object that is less than x.
 * @return the predecessor if it exists, NULL otherwise.
 */
void *dictionary_predecessor(const Dictionary *d, const void *x);

/**
 * Gets the successor of the specified object from the dictionary.
 *
 * @param d the dictionary to get the successor of.
 * @param x the smallest object that is greater than x.
 * @return the successor if it exists, NULL otherwise.
 */
void *dictionary_successor(const Dictionary *d, const void *x);

#endif /* DICTIONARY_H */
