#include "../diag/contract.h"
#include "dictionary.h"

#include <stdlib.h>

void *dictionary_max(const Dictionary *d) {
  contract_requires(d != NULL && !container_empty((Container *)d));
  return d->vtable->max(d);
}

void *dictionary_min(const Dictionary *d) {
  contract_requires(d != NULL && !container_empty((Container *)d));
  return d->vtable->min(d);
}

void *dictionary_predecessor(const Dictionary *d, const void *x) {
  contract_requires(d != NULL && x != NULL && !container_empty((Container *)d));
  return d->vtable->predecessor(d, x);
}

void *dictionary_successor(const Dictionary *d, const void *x) {
  contract_requires(d != NULL && x != NULL && !container_empty((Container *)d));
  return d->vtable->successor(d, x);
}
