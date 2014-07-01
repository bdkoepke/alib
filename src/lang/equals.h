#ifndef EQUALS_H
#define EQUALS_H

#include <stdbool.h>

/**
 * Gets a value indicating whether two objects are equal.
 *
 * @param a the first object.
 * @param b the second object.
 * @return true if they are equal, false otherwise.
 */
typedef bool (*Equals)(const void *a, const void *b);

extern bool equals_int_pointer(const void *, const void *);
extern bool equals_int(const void *, const void *);
extern bool equals_float(const void *, const void *);
extern bool equals_double(const void *, const void *);

#endif /* EQUALS_H */
