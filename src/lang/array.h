#ifndef ARRAY_H
#define ARRAY_H

/**
 * Gets the size of a static array, must be > 0.
 */
#define array_size(a) (sizeof((a)) / sizeof((a)[0]))

/**
 * Writes the specified array to stdout.
 *
 * @param a the array to write.
 * @param length the length of the array.
 */
void array_puts(const int a[], int length);

/**
 * Creates a new copy of the specified array.
 *
 * @param a the array to copy.
 * @param length the length of the array.
 * @return a copy of the array a.
 */
int *array_copy(const int a[], int length);

#endif /* ARRAY_H */
