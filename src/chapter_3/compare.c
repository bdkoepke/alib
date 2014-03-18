#include "compare.h"
#include "type.h"

int compare_int(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}

int compare_float(const void *a, const void *b) {
  return *((float *)a) - *((float *)b);
}
