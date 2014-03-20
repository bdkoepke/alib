#include "binary_node.h"
#include "compare.h"
#include "sorted_set.h"
#include "../contract.h"
#include "type.h"

#include <assert.h>
#include <stdlib.h>

typedef struct {
  sorted_set_vtable *vtable;
  BinaryNode *root;
  Compare c;
} _SortedSet;

typedef struct {
  int k;
  void *x;
} KeyValue;

static KeyValue *key_value_new(int k, void *x) {
  KeyValue *t = malloc(sizeof(KeyValue));
  t->k = k;
  t->x = x;
  return t;
}

static bool __sorted_set_member(const BinaryNode *n, Compare c, const void *x) {
  if (n == NULL)
    return false;
  KeyValue *t = (KeyValue *)n->x;
  int r = c(x, t->x);
  if (r == 0)
    return true;
  return r < 0 ? __sorted_set_member(n->left, c, x)
               : __sorted_set_member(n->right, c, x);
}

static bool _sorted_set_member(const SortedSet *s, const void *x) {
  return __sorted_set_member(((const _SortedSet *)s)->root,
                             ((const _SortedSet *)s)->c, x);
}

static void __sorted_set_insert(BinaryNode *n, BinaryNode **p, Compare c,
                                void *x) {
  if (n == NULL)
    *p = binary_node_new_leaf(key_value_new(0, x));
  else {
    KeyValue *t = (KeyValue *)n->x;
    int r = c(x, t->x);
    BinaryNode **_p;
    if (r > 0)
      _p = &(n->right);
    else {
      _p = &(n->left);
      t->k++;
    }
    __sorted_set_insert(*_p, _p, c, x);
  }
}

static void _sorted_set_insert(SortedSet *_s, void *x) {
  _SortedSet *s = (_SortedSet *)_s;
  __sorted_set_insert(s->root, &(s->root), s->c, x);
}

static KeyValue *sorted_set_min(BinaryNode *root) {
  BinaryNode *n;
  for (n = root; n->left != NULL; n = n->left)
    continue;
  return (KeyValue *)n->x;
}

static void *__sorted_set_delete(BinaryNode *n, BinaryNode **p, size_t k) {
 	KeyValue *t = (KeyValue *)n->x;
 	int r = k - t->k;
  if (r < 0) {
		t->k--;
    return __sorted_set_delete(n->left, &(n->left), k);
	}
  else if (r > 0)
    return __sorted_set_delete(n->right, &(n->right), k);
  else {
    if (binary_node_is_branch(n)) {
      KeyValue *min = sorted_set_min(n->right);
      n->x = min;
      return __sorted_set_delete(n->right, &(n->right), min->k);
    } else {
			*p = (n->left != NULL) ? n->left : n->right;
			void *x = ((KeyValue *)n->x)->x;
			free(n->x);
      free(n);
			return x;
    }
  }
}

static void *_sorted_set_delete(SortedSet *s, size_t k) {
  BinaryNode *root = (((_SortedSet *)s)->root);
  return __sorted_set_delete(root, &(root), k);
}

static bool _sorted_set_empty(const SortedSet *s) {
  return ((const _SortedSet *)s)->root == NULL;
}

static size_t _sorted_set_size(const SortedSet *s) {
	size_t size = 0;
	BinaryNode *root = ((const _SortedSet *)s)->root;
	if (root == NULL)
		return size;
  BinaryNode *n;
  for (n = root; n != NULL; n = n->right)
		size += ((KeyValue *)n->x)->k;
	return size;
}

static void sorted_set_free(Object *o) { assert(false); }

SortedSet *sorted_set_new(Compare c) {
  static sorted_set_vtable vtable = {
    {.free = sorted_set_free },
        .member = _sorted_set_member, .insert = _sorted_set_insert,
        .delete = _sorted_set_delete, .size = _sorted_set_size,
  };

  _SortedSet *s = malloc(sizeof(_SortedSet));
  s->vtable = &vtable;
  s->root = NULL;
  s->c = c;
  return (SortedSet *)s;
}

bool sorted_set_member(const SortedSet *s, const void *x) {
  contract_requires(s != NULL && x != NULL);
  return s->vtable->member(s, x);
}

void sorted_set_insert(SortedSet *s, void *x) {
  contract_requires(s != NULL && x != NULL && !sorted_set_member(s, x));
  s->vtable->insert(s, x);
  contract_ensures(sorted_set_member(s, x));
}

void *sorted_set_delete(SortedSet *s, size_t k) {
  contract_requires(s != NULL && !sorted_set_empty(s) && k <= sorted_set_size(s));
  return s->vtable->delete (s, k);
}

bool sorted_set_empty(const SortedSet *s) {
  contract_requires(s != NULL);
	return sorted_set_size(s) == 0;
}

size_t sorted_set_size(const SortedSet *s) {
	contract_requires(s != NULL);
	return s->vtable->size(s);
}
