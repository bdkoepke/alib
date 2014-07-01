#ifndef SORTED_SET_H
#define SORTED_SET_H

#include "../lang/object.h"
#include "../lang/compare.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct _sorted_set_vtable sorted_set_vtable;
typedef struct SortedSet {
  sorted_set_vtable *vtable;
} SortedSet;
struct _sorted_set_vtable {
  object_vtable object;
  bool (*member)(const SortedSet *, const void *);
  void (*insert)(SortedSet *, void *);
  void *(*delete)(SortedSet *, size_t);
  size_t (*size)(const SortedSet *);
};

/**
 * Creates a new sorted set.
 *
 * @param c the comparison function for the set.
 * @return a new sorted set.
 */
SortedSet *sorted_set_new(Compare c);

/**
 * Gets a value indicating whether the specified object
 * is a member of the sorted set or not.
 *
 * @param s the sorted set to test for membership.
 * @param x the object to check for membership.
 * @return true if the object is a member of the set, false otherwise.
 */
bool sorted_set_member(const SortedSet *s, const void *x);

/**
 * Inserts the specified object into the specified
 * sorted set.
 *
 * @param s the sorted set to insert the object into.
 * @param x the object to insert.
 */
void sorted_set_insert(SortedSet *s, void *x);

/**
 * Deletes the object at the kth position in the set.
 *
 * @param s the set to delete the object from.
 * @param k the position in the set.
 * @return the object that was removed from the set.
 */
void *sorted_set_delete(SortedSet *s, size_t k);

/**
 * Gets a value indicating whether the sorted set
 * is empty or not.
 *
 * @param s the set to determine the emptiness of.
 * @return true if the set is empty, false otherwise.
 */
bool sorted_set_empty(const SortedSet *s);

/**
 * Gets the size of the sorted set.
 *
 * @param s the sorted set to get the size of.
 * @return the size of the sorted set.
 */
size_t sorted_set_size(const SortedSet *s);

#endif /* SORTED_SET_H */
