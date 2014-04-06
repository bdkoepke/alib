#include "../diag/contract.h"
#include "sorted_dictionary.h"

#include <stdlib.h>

void *sorted_dictionary_max(const SortedDictionary *s) {
  contract_requires(s != NULL && !container_empty((Container *)s));
  return s->vtable->max(s);
}

void *sorted_dictionary_min(const SortedDictionary *s) {
  contract_requires(s != NULL && !container_empty((Container *)s));
  return s->vtable->min(s);
}

void *sorted_dictionary_predecessor(const SortedDictionary *s, const void *k) {
  contract_requires(s != NULL && k != NULL && !container_empty((Container *)s));
  return s->vtable->predecessor(s, k);
}

void *sorted_dictionary_successor(const SortedDictionary *s, const void *k) {
  contract_requires(s != NULL && k != NULL && !container_empty((Container *)s));
  return s->vtable->successor(s, k);
}
