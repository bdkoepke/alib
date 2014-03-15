#include "contract.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void _contract_ensures(bool expr, const char *expr_s, const char *file,
                       int line, const char *func) {
  if (!expr) {
    fprintf(stderr, "%s:%d: %s: Ensures `%s' failed.\n", file, line, func,
            expr_s);
	assert (false);
    exit(EXIT_FAILURE);
  }
}

void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func) {
  if (!expr) {
    fprintf(stderr, "%s:%s: %s: Invariant `%s' failed.\n", file, line, func,
            expr_s);
	assert (false);
    exit(EXIT_FAILURE);
  }
}

void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func) {
  if (!expr) {
    fprintf(stderr, "%s:%d: %s: Requires `%s' failed.\n", file, line, func,
            expr_s);
	assert (false);
    exit(EXIT_FAILURE);
  }
}
