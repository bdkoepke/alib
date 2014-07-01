#include "../diag/contract.h"
#include "sorted_dictionary.h"

#include <stdlib.h>

void *sorted_dictionary_max(const SortedDictionary *s) {
  contract_requires(!set_empty((Set *)s));
  return s->vtable->max(contract_requires_non_null(s));
}

void *sorted_dictionary_min(const SortedDictionary *s) {
  contract_requires(!set_empty((Set *)s));
  return s->vtable->min(contract_requires_non_null(s));
}

void *sorted_dictionary_predecessor(const SortedDictionary *s, const void *k) {
  contract_requires(!set_empty((Set *)s));
  return s->vtable->predecessor(contract_requires_non_null(s),
                                contract_requires_non_null(k));
}

void *sorted_dictionary_successor(const SortedDictionary *s, const void *k) {
  contract_requires(!set_empty((Set *)s));
  return s->vtable->successor(contract_requires_non_null(s),
                              contract_requires_non_null(k));
}
