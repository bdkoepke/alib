#include "test.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _assert_true(bool expr, const char *expr_s, const char *file, int line,
                  const char *func) {
  if (!expr) {
    fprintf(stderr, "%s:%d: %s: Test `%s' failed.\n", file, line, func, expr_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
}

void _assert_false(bool expr, const char *expr_s, const char *file, int line,
                   const char *func) {
  if (expr) {
    fprintf(stderr, "%s:%d: %s: Test `%s' failed.\n", file, line, func, expr_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
}

void _assert_equals(int a, int b, const char *a_s, const char *b_s,
                    const char *file, int line, const char *func) {
  if (a != b) {
    fprintf(stderr, "%s:%d: %s: `%d' != `%d'.\n", file, line, func, a, b);
    assert(false);
    exit(EXIT_FAILURE);
  }
}

void _assert_not_equals(int a, int b, const char *a_s, const char *b_s,
                        const char *file, int line, const char *func) {
  if (a == b) {
    fprintf(stderr, "%s:%d: %s: `%d' != `%d'.\n", file, line, func, a, b);
    assert(false);
    exit(EXIT_FAILURE);
  }
}

void _assert_memcmp(const void *a, const void *b, size_t num, const char *a_s,
                    const char *b_s, const char *file, int line,
                    const char *func) {
  if (memcmp(a, b, num)) {
    fprintf(stderr, "%s:%d: %s: `%d' != `%d'.\n", file, line, func, a, b);
    assert(false);
    exit(EXIT_FAILURE);
  }
}
