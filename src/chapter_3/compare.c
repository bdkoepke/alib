#include "compare.h"
#include "type.h"

int compare_int(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}

int compare_float(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}

int compare_double(const void *a, const void *b) {
  double d = POINTER_TO_INT(a) - POINTER_TO_INT(b);
  if (d < 0)
    return -1;
  return d == 0 ? 0 : 1;
}
