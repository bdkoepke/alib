#include "../diag/contract.h"
#include "binary_node.h"
#include "red_black_tree.h"

#include <assert.h>
#include <stdlib.h>

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
                                 RedBlackNode *right, RedBlackNode *parent) {
  RedBlackNode *r = malloc(sizeof(RedBlackNode));
  r->x = x;
  r->c = c;
  r->left = left;
  r->right = right;
  r->parent = parent;
  return r;
}

static RedBlackNode *red_black_node_new_leaf(void *x, Color c, RedBlackNode *parent) {
  return red_black_node_new(x, c, NULL, NULL, parent);
}

static void red_black_tree_free(Object *o) {
  binary_node_free_r((BinaryNode *)((RedBlackTree *)o)->root);
  free(o);
}

static bool red_black_tree_is_valid(RedBlackTree *r) {
	bool red_black_node_is_valid(RedBlackNode *n) {
		if (n == NULL)
			return true;
		if ((n->left != NULL && n->left->parent != n) || (n->right != NULL && n->right->parent != n) || n->parent->c == n->c)
			return false;
		return red_black_node_is_valid(n->left) && red_black_node_is_valid(n->right);
	}
	RedBlackNode *root = r->root;
	if (root == NULL)
		return true;
	return root->c != Black ? false : red_black_node_is_valid(root->left) && red_black_node_is_valid(root->right);
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

static void rotate_right(RedBlackNode *n) {
	puts("rotate_right");
  RedBlackNode *g = grandparent(n), *p = n->parent;
 	g->left = p->right, p->right->parent = g;
	g->parent = p, p->right = g;
}

static void rotate_left(RedBlackNode *n) {
	puts("rotate_left");
  RedBlackNode *g = grandparent(n), *p = n->parent;
  g->right = p->left, p->left->parent = g;
  p->left = g, g->parent = p;
}

static void red_black_tree_insert(Container *c, void *x) {
  void red_black_node_insert(RedBlackNode * n, RedBlackNode * p, Compare c,
                             void * x) {
    void red_black_node_insert_case_1(RedBlackNode * n, Compare c, void * x) {
      void red_black_node_insert_case_2(RedBlackNode * n, Compare c, void * x) {
        void red_black_node_insert_case_3(RedBlackNode * n, Compare c,
                                          void * x) {
          void red_black_node_insert_case_4(RedBlackNode * n, Compare c,
                                            void * x) {
            void red_black_node_insert_case_5(RedBlackNode * n, Compare c,
                                              void * x) {
							puts("case5");
              RedBlackNode *g = grandparent(n);
              n->parent->c = Black, g->c = Red;
              (n == n->parent->left ? rotate_right : rotate_left)(g);
            }
						puts("case4");
            RedBlackNode *g = grandparent(n);
            if (n == n->parent->right && n->parent == g->left) {
              rotate_left(n->parent);
              n = n->left;
            } else if (n == n->parent->left && n->parent == g->right) {
              rotate_right(n->parent);
              n = n->left;
            }
            red_black_node_insert_case_5(n, c, x);
          }
					puts("case3");
          RedBlackNode *u = uncle(n);
          if (u != NULL && u->c == Red) {
            n->parent->c = u->c = Black;
            RedBlackNode *g = grandparent(n);
            g->c = Red;
            red_black_node_insert_case_1(g, c, x);
          } else
            red_black_node_insert_case_4(n, c, x);
        }
				puts("case2");
        if (n->parent->c == Red)
          red_black_node_insert_case_3(n, c, x);
      }
			puts("case1");
      if (n->parent == NULL)
        n->c = Black;
      else
        red_black_node_insert_case_2(n, c, x);
    }

    if (n == NULL) {
			RedBlackNode *leaf = red_black_node_new_leaf(x, Red, p);
			if (c(x, p->x) < 0)
				p->left = leaf;
			else
				p->right = leaf;
      red_black_node_insert_case_1(leaf, c, x);
		}
    else
      red_black_node_insert(c(x, n->x) < 0 ? n->left : n->right, n, c, x);
  }
	printf("%d\n", x);
  RedBlackTree *r = (RedBlackTree *)c;
	contract_invariant(red_black_tree_is_valid(r));
	if (r->root == NULL)
		r->root = red_black_node_new_leaf(x, Black, NULL);
  else
		red_black_node_insert(r->root, NULL, r->c, x);
	contract_invariant(red_black_tree_is_valid(r));
}

static void red_black_tree_delete(Container *c, const void *x) {
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
                  s->right->c = Black, rotate_left(n->parent);
                else
                  s->left->c = Black, rotate_right(n->parent);
              }
              RedBlackNode *s = sibling(n);
              if (s->c == Black) {
                if (n == n->parent->left && s->right->c == Black &&
                    s->left->c == Red) {
                  s->c = Red, s->left->c = Black;
                  rotate_right(s);
                } else if (n == n->parent->right && s->left->c == Black &&
                           s->right->c == Red) {
                  s->c = Red, s->right->c = Black;
                  rotate_left(s);
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
          (n == n->parent->left ? rotate_left : rotate_right)(n->parent);
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
          /*else
            red_black_node_delete_case_1(child, c, x); */
        }
      }
      free(n);
    }
  }
  RedBlackTree *r = (RedBlackTree *)c;
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
    { { {.free = red_black_tree_free },
            .search = red_black_tree_search, .insert = red_black_tree_insert,
            .delete = red_black_tree_delete, .empty = red_black_tree_empty },
          .max = red_black_tree_max, .min = red_black_tree_min,
          .predecessor = red_black_tree_predecessor,
          .successor = red_black_tree_successor },
        .pre_order = red_black_tree_pre_order, .in_order =
                                                   red_black_tree_in_order,
        .post_order = red_black_tree_post_order, .level_order =
                                                     red_black_tree_level_order
  };

  contract_requires(c != NULL);
  RedBlackTree *r = malloc(sizeof(RedBlackTree));
  r->vtable = &vtable;
  r->root = NULL;
  r->c = c;
  return (Tree *)r;
}
