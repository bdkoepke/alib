#ifndef ARRAY_CONTAINER_H
#define ARRAY_CONTAINER_H

#include "container.h"

#include <stddef.h>

/**
 * Creates a new array container that has constant time search,
 * insertion, and deletion where the maximum item value is bounded.
 * 
 * I.e. in java this would be ArrayContainer : Container<Integer>
 * with the additional condition that you can only insert integers
 * that are strictly less than the specified max.
 *
 * @param max the maximum integer that can be inserted.
 */
Container *array_container_new(size_t max);

#endif /* ARRAY_CONTAINER_H */
