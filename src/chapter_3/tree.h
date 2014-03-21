#ifndef TREE_H
#define TREE_H

#include "linked_stack.h"
#include "dictionary.h"
#include "visitor.h"

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

LinkedStack *tree_to_linked_stack(Tree *);

#endif /* TREE_H */
