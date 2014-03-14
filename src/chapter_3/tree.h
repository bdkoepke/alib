#ifndef TREE_H
#define TREE_H

#include "dictionary.h"

typedef bool (*Visitor)(void *, void *x);
typedef struct _tree_vtable tree_vtable;
typedef struct Tree {
  tree_vtable *vtable;
} Tree;
struct _tree_vtable {
  dictionary_vtable dictionary;
  void (*pre_order)(Tree *, Visitor, void *);
  void (*in_order)(Tree *, Visitor, void *);
  void (*post_order)(Tree *, Visitor, void *);
  void (*level_order)(Tree *, Visitor, void *);
};

void tree_pre_order(Tree *, Visitor, void *);
void tree_in_order(Tree *, Visitor, void *);
void tree_post_order(Tree *, Visitor, void *);
void tree_level_order(Tree *, Visitor, void *);

#endif /* TREE_H */
