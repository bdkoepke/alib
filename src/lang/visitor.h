#ifndef VISITOR_H
#define VISITOR_H

#include "../util/key_value_pair.h"

typedef void (*Visitor)(void *user_data, const KeyValuePair *p);

#endif /* Visitor */
