#include "compare.h"
#include "type.h"

#include <assert.h>

int compare_int_pointer(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}

int compare_int(const void *a, const void *b) {
  return *((int *)a) - *((int *)b);
}

int compare_float(const void *a, const void *b) {
  float d = *(float *)a - *(float *)b;
  if ((d < 1 && d > 0) || (d > -1 && d < 0))
    return d == 0 ? 0 : (d < 0 ? -1 : 1);
  return d;
}

int compare_double(const void *a, const void *b) {
  double d = *(double *)a - *(double *)b;
  if ((d < 1 && d > 0) || (d > -1 && d < 0))
    return d == 0 ? 0 : (d < 0 ? -1 : 1);
  return d;
}
