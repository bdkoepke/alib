#include "contract.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static inline void contract(bool expr, const char *expr_s, const char *file,
                       int line, const char *func, const char *format) {
  if (!expr) {
    fprintf(stderr, format, file, line, func,
            expr_s);
    assert(false);
    exit(EXIT_FAILURE);
  }
}


void _contract_ensures(bool expr, const char *expr_s, const char *file,
                       int line, const char *func) {
	return contract(expr, expr_s, file, line, func, "%s:%d: %s: Ensures `%s' failed.\n");
}

void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func) {
	return contract(expr, expr_s, file, line, func, "%s:%d: %s: Invariant `%s' failed.\n");
}

void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func) {
	return contract(expr, expr_s, file, line, func, "%s:%d: %s: Requires `%s' failed.\n");
}
