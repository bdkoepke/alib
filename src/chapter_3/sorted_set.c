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

KeyValue *key_value_new(int k, void *x) {
  KeyValue *t = malloc(sizeof(KeyValue));
  t->k = k;
  t->x = x;
  return t;
}

bool __sorted_set_member(const BinaryNode *n, Compare c, const void *x) {
  if (n == NULL)
    return false;
  KeyValue *t = (KeyValue *)(n->x);
  int r = c(x, t->x);
  if (r == 0)
    return true;
  return r < 0 ? binary_node_search(n->left, c, x)
               : binary_node_search(n->right, c, x);
}

static bool _sorted_set_member(const SortedSet *s, const void *x) {
  return __sorted_set_member(((const _SortedSet *)s)->root,
                             ((const _SortedSet *)s)->c, x);
}

static void __sorted_set_insert(BinaryNode *n, BinaryNode **p, Compare c,
                                void *x) {
  if (n == NULL)
    *p = binary_node_new_leaf(key_value_new(1, x));
  else {
    int r = c(x, INT_TO_POINTER(((KeyValue *)(n->x))->k));
    BinaryNode **_p;
    if (r > 0) {
      _p = &(n->right);
    } else {
      _p = &(n->left);
      ((KeyValue *)((*p)->x))->k++;
    }
    binary_node_insert(*_p, _p, c, x);
  }
}

static void _sorted_set_insert(SortedSet *_s, void *x) {
  _SortedSet *s = (_SortedSet *)_s;
  __sorted_set_insert(s->root, &(s->root), s->c, x);
}

void __sorted_set_delete(BinaryNode *n, BinaryNode **p, int k) {
  assert(false);
  /*
 	KeyValue *t = (KeyValue *)n;
 	int r = k - t->k;
   if (r < 0)
     binary_node_delete(n->left, &(n->left), k);
   else if (r > 0)
     binary_node_delete(n->right, &(n->right), k);
   else {
     if (binary_node_is_branch(n)) {
       void *min = binary_node_min(n->right);
       n->x = min;
       binary_node_delete(n->right, &(n->right), k);
     } else {
       if (n->left != NULL) {
         *p = n->left;
 				t->k--;
       } else if (n->right != NULL)
         *p = n->right;
       else
         *p = NULL;
       free(n);
     }
   }
 	*/
}

static void _sorted_set_delete(SortedSet *s, int k) {
  BinaryNode *root = (((_SortedSet *)s)->root);
  __sorted_set_delete(root, &(root), k);
}

static bool _sorted_set_empty(const SortedSet *s) {
  return ((const _SortedSet *)s)->root == NULL;
}

static size_t sorted_set_size(const SortedSet *s) {
  if (_sorted_set_empty(s))
    return 0;
  BinaryNode *n;
  for (n = ((const _SortedSet *)s)->root; n->right != NULL; n = n->right)
    continue;
  return ((KeyValue *)(n->x))->k;
}

static void sorted_set_free(Object *o) { assert(false); }

SortedSet *sorted_set_new(Compare c) {
  static sorted_set_vtable vtable = {
    {.free = sorted_set_free },
        .member = _sorted_set_member, .insert = _sorted_set_insert,
        .delete = _sorted_set_delete, .empty = _sorted_set_empty,
  };

  _SortedSet *s = malloc(sizeof(_SortedSet));
  s->vtable = &vtable;
  s->root = NULL;
  s->c = c;
  return (SortedSet *)s;
}

bool sorted_set_member(const SortedSet *s, const void *x) {
  contract_requires(s != NULL);
  s->vtable->member(s, x);
}

void sorted_set_insert(SortedSet *s, void *x) {
  contract_requires(s != NULL && !sorted_set_member(s, x));
  s->vtable->insert(s, x);
  contract_ensures(sorted_set_member(s, x));
}

void sorted_set_delete(SortedSet *s, int k) {
  contract_requires(s != NULL && !sorted_set_empty(s) &&
                    k < sorted_set_size(s));
  s->vtable->delete (s, k);
}

bool sorted_set_empty(const SortedSet *s) {
  contract_requires(s != NULL);
  return s->vtable->empty(s);
}
