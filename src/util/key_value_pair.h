#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

typedef struct {
  void const *k;
  void *v;
} KeyValuePair;

KeyValuePair *key_value_pair_new(void const *k, void *v);

#endif /* KEY_VALUE_PAIR_H */
