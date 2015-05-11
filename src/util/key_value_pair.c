#include "key_value_pair.h"

#include <stdlib.h>

KeyValuePair *key_value_pair_new(void const *k, void *v) {
  KeyValuePair *p = malloc(sizeof(KeyValuePair));
  p->k = k;
  p->v = v;
  return p;
}
