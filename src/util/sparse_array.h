#ifndef SPARSE_ARRAY_H
#define SPARSE_ARRAY_H

#include "mutable_container.h"

/**
 * Creates a new sparse array.
 *
 * @param n the maximum object size that can be inserted into the array.
 * @param m the maximum number of objects that can be inserted
 * 	into the array.
 * @return a new empty sparse array.
 */
MutableContainer *sparse_array_new(unsigned int n, unsigned int m);

#endif /* SPARSE_ARRAY_H */
