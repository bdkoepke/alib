#include "equals.h"
#include "type.h"

bool equals_int_pointer(const void *a, const void *b) {
  return POINTER_TO_INT(a) == POINTER_TO_INT(b);
}

bool equals_int(const void *a, const void *b) {
  return *((int *)a) == *((int *)b);
}

bool equals_float(const void *a, const void *b) {
  return *(float *)a == *(float *)b;
}

bool equals_double(const void *a, const void *b) {
  return *(double *)a == *(double *)b;
}
