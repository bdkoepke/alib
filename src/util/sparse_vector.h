#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

#include "vector.h"

/**
 * Creates a new sparse vector.
 *
 * @param n the maximum object size that can be inserted into the vector.
 * @param m the maximum number of objects that can be inserted
 *      into the vector.
 * @return a new empty sparse vector.
 */
Vector *sparse_vector_new(unsigned int n, unsigned int m);

#endif /* SPARSE_VECTOR_H */
