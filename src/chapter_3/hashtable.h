#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "container.h"

#include <stddef.h>

typedef size_t (*Hash)(const void *);

Container *hashtable_new(Hash);

#endif /* HASHTABLE_H */
