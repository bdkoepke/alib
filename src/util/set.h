#ifndef SET_H
#define SET_H

#include "container.h"

#include <stdbool.h>

typedef struct _set_vtable set_vtable;
typedef struct Set {
  set_vtable *vtable;
} Set;
struct _set_vtable {
  iterable_vtable iterable;
  const void *(*search)(const Set *, const void *);
  void (*insert)(Set *, void *);
  void *(*delete)(Set *, const void *);
  bool (*empty)(const Set *);
};

/**
 * Searches the specified set for the specified item.
 *
 * @param s the set to search.
 * @param x the object to search for.
 * @return the object x from the set if it exists, NULL otherwise.
 */
const void *set_search(const Set *s, const void *x);

/**
 * Gets a value indicating whether the set is empty or not.
 *
 * @param s the set to check for emptiness.
 * @return true if the set is empty, false otherwise.
 */
bool set_empty(const Set *s);

/**
 * Inserts the specified object into the set.
 *
 * @param s the set to insert the object into.
 * @param x the object to insert into the set.
 */
void set_insert(Set *s, void *x);

/**
 * Deletes the specified object from the set.
 *
 * @param s the set to delete the object from.
 * @param x the object to delete from the set.
 * @return a pointer to the element that was deleted.
 */
void *set_delete(Set *s, const void *x);

#endif /* SET_H */
