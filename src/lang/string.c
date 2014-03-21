#include "string.h"
#include <string.h>

int find_match(const char *pattern, const char *text) {
  int m = strlen(pattern);
  int n = strlen(text);

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
