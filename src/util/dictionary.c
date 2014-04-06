#include "../diag/contract.h"
#include "dictionary.h"

#include <stdlib.h>

inline void dictionary_insert(Dictionary *d, const void *k, void *v) {
	contract_requires(d != NULL && k != NULL && v != NULL);
	contract_weak_requires(container_search((Container *)d, k) == NULL);
	d->vtable->insert(d, k, v);
	contract_ensures(container_search((Container *)d, k) == v);
}

void *dictionary_reassign(Dictionary *d, const void *k, void *v) {
	contract_requires(d != NULL && k != NULL && v != NULL);
	contract_weak_requires(container_search((Container *)d, k) != NULL);
	void *_v = d->vtable->reassign(d, k, v);
	contract_ensures(container_search((Container *)d, k) == v);
	return _v;
}

void *dictionary_delete(Dictionary *d, const void *k) {
	contract_requires(d != NULL && k != NULL);
	void *v = container_search((Container *)d, v);
	contract_invariant(v);
	container_delete((Container *)d, k);
	return v;
}

void _container_insert(Container *d, void *k) {
	dictionary_insert((Dictionary *)d, k, k);
}
