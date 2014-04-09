#include "../diag/contract.h"
#include "../lang/type.h"
#include "binary_node.h"
#include "sorted_set.h"

#include <stdlib.h>

typedef struct {
  sorted_set_vtable *vtable;
  BinaryNode *root;
  Compare c;
} _SortedSet;

static bool _sorted_set_member(const SortedSet *s, const void *k) {
  bool __sorted_set_member(const BinaryNode * n, Compare c, const void * k) {
    if (n == NULL)
      return false;
    KeyValuePair t = n->p;
    int r = c(k, t.k);
    if (r == 0)
      return true;
    return r < 0 ? __sorted_set_member(n->left, c, k)
                 : __sorted_set_member(n->right, c, k);
  }
  return __sorted_set_member(((const _SortedSet *)s)->root,
                             ((const _SortedSet *)s)->c, k);
}

static void _sorted_set_insert(SortedSet *_s, void *k) {
  void __sorted_set_insert(BinaryNode * n, BinaryNode * *p, Compare c,
                           void * k) {
    if (n == NULL)
      *p = binary_node_new_leaf(0, k);
    else {
      KeyValuePair t = n->p;
      int r = c(k, t.k);
      BinaryNode **_p = (r > 0) ? &(n->right) : (t.k++, &(n->left));
      __sorted_set_insert(*_p, _p, c, k);
    }
  }
  _SortedSet *s = (_SortedSet *)_s;
  __sorted_set_insert(s->root, &(s->root), s->c, k);
}

static KeyValuePair *sorted_set_min(BinaryNode *root) {
  BinaryNode *n;
  for (n = root; n->left != NULL; n = n->left)
    continue;
  return &(n->p);
}

static void *_sorted_set_delete(SortedSet *s, size_t k) {
  void *__sorted_set_delete(BinaryNode * n, BinaryNode * *p, size_t k) {
    KeyValuePair t = n->p;
    /*
  		printf("k: %d, t->k: %d\n", k, t->k);
  		 int r = k - t->k;
  		 if (r < 0) {
  			 t->k--;
  			 return __sorted_set_delete(n->left, &(n->left), k);
  		 } else if (r > 0)
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
  		*/
  }
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
    size += POINTER_TO_INT(n->p.k) + 1;
  return size;
}

static void sorted_set_free(Object *o) {
  SortedSet *s = (SortedSet *)o;
  puts("sorted_set_free implementation slow");
  while (!sorted_set_empty(s))
    sorted_set_delete(s, 0);
  free(s);
}

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
  return s->vtable
      ->member(contract_requires_non_null(s), contract_requires_non_null(x));
}

void sorted_set_insert(SortedSet *s, void *x) {
  contract_weak_requires(!sorted_set_member(s, x));
  s->vtable
      ->insert(contract_requires_non_null(s), contract_requires_non_null(x));
  contract_weak_ensures(sorted_set_member(s, x));
}

void *sorted_set_delete(SortedSet *s, size_t k) {
  contract_requires(!sorted_set_empty(s) && k <= sorted_set_size(s));
  return s->vtable->delete (contract_requires_non_null(s), k);
}

bool sorted_set_empty(const SortedSet *s) {
  return sorted_set_size(contract_requires_non_null(s)) == 0;
}

size_t sorted_set_size(const SortedSet *s) {
  return s->vtable->size(contract_requires_non_null(s));
}
