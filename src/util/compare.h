#ifndef COMPARE_H
#define COMPARE_H

/**
 * Compares two objects for ordering.
 *
 * @param a the first object.
 * @param b the second object.
 * @return < 0 if a < b, 0 if a == b, > 0 if a > b
 */
typedef int (*Compare)(const void *a, const void *b);

/** Compares two integers stored as pointers. */
extern int compare_int_pointer(const void *, const void *);

/** Normal qsort style comparison functions */
extern int compare_int(const void *, const void *);
extern int compare_float(const void *, const void *);
extern int compare_double(const void *, const void *);

#endif /* COMPARE_H */
