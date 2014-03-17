#include "compare.h"
#include "contract.h"
#include "limits.h"
#include "stdbool.h"
#include "type.h"

int compare_int(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}
