#include "../diag/contract.h"
#include "dictionary.h"

#include <stdlib.h>

void *dictionary_search(const Dictionary *d, const void *k) {
  return d->vtable
      ->search(contract_requires_non_null(d), contract_requires_non_null(k));
}

bool dictionary_empty(const Dictionary *d) {
  return d->vtable->empty(contract_requires_non_null(d));
}

void dictionary_insert(Dictionary *d, const void *k, void *v) {
  contract_weak_requires_equal(dictionary_search(d, k), NULL);
  d->vtable
      ->insert(contract_requires_non_null(d), contract_requires_non_null(k),
               contract_requires_non_null(v));
  contract_weak_ensures_equal(dictionary_search(d, k), v);
}

void *dictionary_reassign(Dictionary *d, const void *k, void *v) {
  contract_weak_requires_non_null(dictionary_search(d, k));
  void *o = contract_ensures_non_null(d->vtable->reassign(
      contract_requires_non_null(d), contract_requires_non_null(k),
      contract_requires_non_null(v)));
  contract_weak_ensures_equal(dictionary_search(d, k), v);
  return o;
}

void *dictionary_delete(Dictionary *d, const void *k) {
  contract_weak_requires_non_null(dictionary_search(d, k));
  void *o = contract_ensures_non_null(d->vtable->delete (
      contract_requires_non_null(d), contract_requires_non_null(k)));
  contract_weak_ensures_equal(dictionary_search(d, k), NULL);
  return o;
}

Set *set_from_dictionary(Dictionary *d) {
  contract_requires_non_null(d);
  contract_requires(dictionary_empty(d) && false);
}
