#include "contract.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline void contract(bool expr, const char *expr_s, const char *file,
                            int line, const char *func, const char *format) {
  if (!expr) {
    fprintf(stderr, format, file, line, func, expr_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
}

static inline void *contract_non_null(const void *x, const char *x_s,
                                      const char *file, int line,
                                      const char *func, const char *format) {
  if (x == NULL) {
    fprintf(stderr, format, file, line, func, x_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
  return (void *)x;
}

static inline void *contract_equal(const void *a, const void *b,
                                   const char *a_s, const char *b_s,
                                   const char *file, int line, const char *func,
                                   const char *format) {
  if (a != b) {
    fprintf(stderr, format, file, line, func, a_s, b_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
  return (void *)a;
}

void _contract_ensures(bool expr, const char *expr_s, const char *file,
                       int line, const char *func) {
  contract(expr, expr_s, file, line, func, "%s:%d: %s: Ensures `%s' failed.\n");
}
void *_contract_ensures_non_null(const void *x, const char *x_s,
                                 const char *file, int line, const char *func) {
  return contract_non_null(x, x_s, file, line, func,
                           "%s:%d: %s: Ensures `%s' != NULL failed.\n");
}
void *_contract_ensures_equal(const void *a, const void *b, const char *a_s,
                              const char *b_s, const char *file, int line,
                              const char *func) {
  return contract_equal(a, b, a_s, b_s, file, line, func,
                        "%s:%d: %s: Ensures `%s' == `%s' failed.\n");
}

void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func) {
  contract(expr, expr_s, file, line, func,
           "%s:%d: %s: Invariant `%s' failed.\n");
}
void *_contract_invariant_non_null(const void *x, const char *x_s,
                                   const char *file, int line,
                                   const char *func) {
  return contract_non_null(x, x_s, file, line, func,
                           "%s:%d: %s: Invariant `%s' != NULL failed.\n");
}

void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func) {
  contract(expr, expr_s, file, line, func,
           "%s:%d: %s: Requires `%s' failed.\n");
}
void *_contract_requires_non_null(const void *x, const char *x_s,
                                  const char *file, int line,
                                  const char *func) {
  return contract_non_null(x, x_s, file, line, func,
                           "%s:%d: %s: Requires `%s' != NULL failed.\n");
}
void *_contract_requires_equal(const void *a, const void *b, const char *a_s,
                               const char *b_s, const char *file, int line,
                               const char *func) {
  return contract_equal(a, b, a_s, b_s, file, line, func,
                        "%s:%d: %s: Requires `%s' == `%s' failed.\n");
}
