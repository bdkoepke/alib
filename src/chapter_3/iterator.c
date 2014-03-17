#include "iterator.h"

void *iterator_current(Iterator *i) { return i->vtable->current(i); }

bool iterator_move_next(Iterator *i) { return i->vtable->move_next(i); }
