#include "tuple.h"

Tuple *tuple_new(void *first, void *second) {
	Tuple *t = malloc(sizeof(Tuple));
	t->first = first;
	t->second = second;
	return t;
}
