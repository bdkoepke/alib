#include "../diag/contract.h"
#include "binary_node.h"
#include "red_black_tree.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Color {
  Red,
  Black
} Color;
typedef struct RedBlackNode {
  void *x;
  struct RedBlackNode *left;
  struct RedBlackNode *right;
  struct RedBlackNode *parent;
  Color c;
} RedBlackNode;
typedef struct {
  tree_vtable *vtable;
  RedBlackNode *root;
  Compare c;
} RedBlackTree;

static RedBlackNode *red_black_node_new(void *x, Color c, RedBlackNode *left,
                                        RedBlackNode *right,
                                        RedBlackNode *parent) {
  RedBlackNode *r = malloc(sizeof(RedBlackNode));
  r->x = x;
  r->c = c;
  r->left = left;
  r->right = right;
  r->parent = parent;
  return r;
}

static RedBlackNode *red_black_node_new_leaf(void *x, Color c,
                                             RedBlackNode *parent) {
  return red_black_node_new(x, c, NULL, NULL, parent);
}

static void red_black_tree_free(Object *o) {
  binary_node_free_r((BinaryNode *)((RedBlackTree *)o)->root);
  free(o);
}

static bool red_black_tree_is_valid(RedBlackTree *r) {
  puts("red_black_tree_is_valid");
  bool red_black_node_is_valid(RedBlackNode * n) {
    if (n == NULL)
      return true;
    if (n->left != NULL && n->left->parent != n) {
      if (n->left->parent == NULL)
        printf("n: %d n->left: %d n->left->parent: NULL\n", n->x, n->left->x);
      else
        printf("n: %d n->left: %d n->left->parent: %d\n", n->x, n->left->x,
               n->left->parent->x);
      return puts("invalid left parent"), false;
    }
    if (n->right != NULL && n->right->parent != n)
      return puts("invalid right parent"), false;
    if (n->parent != NULL && n->parent->c == n->c)
      return puts("invalid parent"), false;
    return red_black_node_is_valid(n->left) &&
           red_black_node_is_valid(n->right);
  }
  RedBlackNode *root = r->root;
  if (root == NULL)
    return true;
  return root->c != Black ? false : red_black_node_is_valid(root->left) &&
                                        red_black_node_is_valid(root->right);
}

static RedBlackNode *grandparent(RedBlackNode *n) {
  return (n != NULL && n->parent != NULL) ? n->parent->parent : NULL;
}

static RedBlackNode *uncle(RedBlackNode *n) {
  RedBlackNode *g = grandparent(n);
  return g == NULL ? NULL : n->parent == g->left ? g->right : g->left;
}

static RedBlackNode *sibling(RedBlackNode *n) {
  return n == n->parent->left ? n->parent->right : n->parent->left;
}

static void rotate_right(RedBlackNode *n, RedBlackTree *r) {
  //contract_requires(n->parent != NULL);
  //contract_requires(grandparent(n) != NULL);
  assert(n->c == Red);
  assert(n->parent->c == Black);
  assert(grandparent(n)->c == Red);
  assert(uncle(n) == NULL || uncle(n)->c == Black);
  RedBlackNode *g = grandparent(n), *p = n->parent;
  if (g->parent == NULL)
    p->parent = NULL, r->root = p;
  else {
    assert(false);
    RedBlackNode **gp =
        g->parent->left == g ? &(g->parent->left) : &(g->parent->right);
    p->parent = *gp, *gp = p;
  }
  p->right = g, g->parent = p;

  assert(n->c == Red);
  assert(n->parent->c == Black);
  assert(sibling(n)->c == Red);
  assert(sibling(n)->right == NULL || sibling(n)->right->c == Black);
  assert(r->root->c == Black && r->root == p);

  p = n->parent;
  g = p->right;
  assert(n->parent == p);
  assert(p->parent == NULL);
  assert(p->left == n);
  assert(p->right == g);
  assert(g->parent == p);
  assert(r->root == p);
  puts("rotate right contracts fulfilled");
}

static void rotate_left(RedBlackNode *n, RedBlackTree *r) {
  assert(false);
  contract_requries_non_null(n->parent);
  contract_requires_non_null(grandparent(n));
  RedBlackNode *g = grandparent(n), *p = n->parent;
  if (g->parent == NULL)
    p->parent = NULL, r->root = p;
  else {
    RedBlackNode **gp =
        g->parent->left == g ? &(g->parent->left) : &(g->parent->right);
    p->parent = *gp, *gp = p;
  }
  p->left = g, g->parent = p;
}

static void red_black_tree_insert(Container *c, void *x) {
  RedBlackTree *r = (RedBlackTree *)c;
  void red_black_node_insert(RedBlackNode * n, RedBlackNode * p, Compare c,
                             void * x) {
    void red_black_node_insert_case_1(RedBlackNode * n) {
      void red_black_node_insert_case_2(RedBlackNode * n) {
        void red_black_node_insert_case_3(RedBlackNode * n) {
          void red_black_node_insert_case_4(RedBlackNode * n) {
            void red_black_node_insert_case_5(RedBlackNode * n) {
              RedBlackNode *g = grandparent(n);
              n->parent->c = Black, g->c = Red;
              (n == n->parent->left ? rotate_right : rotate_left)(n, r);
            }
            RedBlackNode *g = grandparent(n);
            if (n == n->parent->right && n->parent == g->left) {
              puts("case4: n->parent->right");
              rotate_left(n->parent, r);
              n = n->left;
            } else if (n == n->parent->left && n->parent == g->right) {
              puts("case4: n->parent->left");
              rotate_right(n->parent, r);
              n = n->right;
            }
            red_black_node_insert_case_5(n);
          }
          RedBlackNode *u = uncle(n);
          if (u != NULL && u->c == Red) {
            n->parent->c = u->c = Black;
            RedBlackNode *g = grandparent(n);
            g->c = Red;
            red_black_node_insert_case_1(g);
          } else
            red_black_node_insert_case_4(n);
        }
        if (n->parent->c == Red)
          red_black_node_insert_case_3(n);
      }
      if (n->parent == NULL)
        n->c = Black;
      else
        red_black_node_insert_case_2(n);
    }

    if (n == NULL) {
      RedBlackNode *leaf = red_black_node_new_leaf(x, Red, p);
      if (c(x, p->x) < 0)
        p->left = leaf;
      else
        p->right = leaf;
      red_black_node_insert_case_1(leaf);
    } else
      red_black_node_insert(c(x, n->x) < 0 ? n->left : n->right, n, c, x);
  }
  contract_invariant(red_black_tree_is_valid(r));
  if (r->root == NULL)
    r->root = red_black_node_new_leaf(x, Black, NULL);
  else
    red_black_node_insert(r->root, NULL, r->c, x);
  contract_invariant(red_black_tree_is_valid(r));
}

static void red_black_tree_delete(Container *c, const void *x) {
  RedBlackTree *r = (RedBlackTree *)c;
  void red_black_node_delete(RedBlackNode * n, RedBlackNode * *p, Compare c,
                             const void * x) {
    void red_black_node_delete_case_1(RedBlackNode * n, Compare c,
                                      const void * x) {
      void red_black_node_delete_case_2(RedBlackNode * n, Compare c,
                                        const void * x) {
        void red_black_node_delete_case_3(RedBlackNode * n, Compare c,
                                          const void * x) {
          void red_black_node_delete_case_4(RedBlackNode * n, Compare c,
                                            const void * x) {
            void red_black_node_delete_case_5(RedBlackNode * n, Compare c,
                                              const void * x) {
              void red_black_node_delete_case_6(RedBlackNode * n, Compare c,
                                                const void * x) {
                RedBlackNode *s = sibling(n);
                s->c = n->parent->c, n->parent->c = Black;
                if (n == n->parent->left)
                  s->right->c = Black, rotate_left(n->parent, r);
                else
                  s->left->c = Black, rotate_right(n->parent, r);
              }
              RedBlackNode *s = sibling(n);
              if (s->c == Black) {
                if (n == n->parent->left && s->right->c == Black &&
                    s->left->c == Red) {
                  s->c = Red, s->left->c = Black;
                  rotate_right(s, r);
                } else if (n == n->parent->right && s->left->c == Black &&
                           s->right->c == Red) {
                  s->c = Red, s->right->c = Black;
                  rotate_left(s, r);
                }
              }
              red_black_node_delete_case_6(n, c, x);
            }
            RedBlackNode *s = sibling(n);
            if (n->parent == Red && Black == s->c == s->left->c == s->right->c)
              s->c = Red, n->parent->c = Black;
            else
              red_black_node_delete_case_5(n, c, x);
          }
          RedBlackNode *s = sibling(n);
          if (Black == n->parent->c == s->c == s->left->c == s->right->c)
            s->c = Red, red_black_node_delete_case_1(n->parent, c, x);
          else
            red_black_node_delete_case_4(n, c, x);
        }
        RedBlackNode *s = sibling(n);
        if (s->c == Red) {
          n->parent->c = Red, s->c = Black;
          (n == n->parent->left ? rotate_left : rotate_right)(n->parent, r);
        }
        red_black_node_delete_case_3(n, c, x);
      }
      if (n->parent != NULL)
        red_black_node_delete_case_2(n, c, x);
    }
    int r = c(x, n->x);
    if (r < 0)
      red_black_node_delete(n->left, &(n->left), c, x);
    else if (r > 0)
      red_black_node_delete(n->right, &(n->right), c, x);
    else if (binary_node_is_branch((BinaryNode *)n)) {
      n->x = binary_node_min((BinaryNode *)n->right);
      red_black_node_delete(n->right, &(n->right), c, n->x);
    } else {
      RedBlackNode *child = (n->left != NULL) ? n->left : n->right;
      *p = child;
      if (child != NULL) {
        child->parent = n->parent;
        if (n->c == Black) {
          if (child->c == Red)
            child->c = Black;
          else
            red_black_node_delete_case_1(child, c, x);
        }
      }
      free(n);
    }
  }
  contract_invariant(red_black_tree_is_valid(r));
  red_black_node_delete(r->root, &(r->root), r->c, x);
  contract_invariant(red_black_tree_is_valid(r));
}

static void *red_black_tree_search(const Container *c, const void *x) {
  return binary_node_search((const BinaryNode *)((const RedBlackTree *)c)->root,
                            ((const RedBlackTree *)c)->c, x);
}

static bool red_black_tree_empty(const Container *c) {
  return binary_node_empty((const BinaryNode *)((const RedBlackTree *)c)->root);
}

static void *red_black_tree_max(const Dictionary *d) {
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_max((const BinaryNode *)((const RedBlackTree *)d)
                                   ->root);
}

static void *red_black_tree_min(const Dictionary *d) {
  return container_empty((const Container *)d)
             ? NULL
             : binary_node_min((const BinaryNode *)((const RedBlackTree *)d)
                                   ->root);
}

static void *red_black_tree_predecessor(const Dictionary *d, const void *x) {
  return binary_node_predecessor(
      (const BinaryNode *)((const RedBlackTree *)d)->root,
      ((const RedBlackTree *)d)->c, x);
}

static void *red_black_tree_successor(const Dictionary *d, const void *x) {
  return binary_node_successor(
      (const BinaryNode *)((const RedBlackTree *)d)->root,
      ((const RedBlackTree *)d)->c, x);
}

static void red_black_tree_pre_order(const Tree *t, Visitor v,
                                     void *user_data) {
  return binary_node_pre_order(
      (const BinaryNode *)((const RedBlackTree *)t)->root, v, user_data);
}

static void red_black_tree_in_order(const Tree *t, Visitor v, void *user_data) {
  return binary_node_in_order(
      (const BinaryNode *)((const RedBlackTree *)t)->root, v, user_data);
}

static void red_black_tree_post_order(const Tree *t, Visitor v,
                                      void *user_data) {
  return binary_node_post_order(
      (const BinaryNode *)((const RedBlackTree *)t)->root, v, user_data);
}

static void red_black_tree_level_order(const Tree *t, Visitor v,
                                       void *user_data) {
  return binary_node_level_order(
      (const BinaryNode *)((const RedBlackTree *)t)->root, v, user_data);
}

Tree *red_black_tree_new(Compare c) {
  static tree_vtable vtable = {
    { { { {.free = red_black_tree_free }, .iterator = NULL },
            .search = red_black_tree_search, .empty = red_black_tree_empty,
            .delete = red_black_tree_delete, .insert = red_black_tree_insert },
          .max = red_black_tree_max, .min = red_black_tree_min,
          .predecessor = red_black_tree_predecessor,
          .successor = red_black_tree_successor },
        .pre_order = red_black_tree_pre_order, .in_order =
                                                   red_black_tree_in_order,
        .post_order = red_black_tree_post_order, .level_order =
                                                     red_black_tree_level_order
  };

  RedBlackTree *r = malloc(sizeof(RedBlackTree));
  r->c = contract_requires_non_null(c);
  r->vtable = &vtable;
  r->root = NULL;
  return (Tree *)r;
}
