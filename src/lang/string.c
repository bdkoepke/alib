#include "../diag/contract.h"
#include "string.h"

#include <stdlib.h>

int find_match(const char *pattern, const char *text, int m, int n) {
	contract_requires(pattern != NULL && text != NULL);
  int i;
  for (i = 0; i <= (n - m); i++) {
    int j;
    for (j = 0; j < m && text[i + j] == pattern[j]; j++)
      continue;
    if (j == m)
      return i;
  }
  return -1;
}
