#include "compare.h"
#include "type.h"

int compare_int_pointer(const void *a, const void *b) {
  return POINTER_TO_INT(a) - POINTER_TO_INT(b);
}

int compare_double_pointer(const void *a, const void *b) {
  double _a = (double)(long)a;
  double _b = (double)(long)b;
  if (((_a < 1 && _a > 0) || (_a > -1 && _a < 0)) &&
      ((_b < 1 && _b > 0) || (_b > -1 && _b < 0))) {
    double d = _a - _b;
    if (d < 0)
      return -1;
    return d == 0 ? 0 : 1;
  }
  return _a - _b;
}

int compare_int(const void *a, const void *b) {
  return *((int *)a) - *((int *)b);
}

int compare_float(const void *a, const void *b) {
  float _a = *((float *)a);
  float _b = *((float *)b);
  if (((_a < 1 && _a > 0) || (_a > -1 && _a < 0)) &&
      ((_b < 1 && _b > 0) || (_b > -1 && _b < 0))) {
    float d = _a - _b;
    if (d < 0)
      return -1;
    return d == 0 ? 0 : 1;
  }
  return _a - _b;
}

int compare_double(const void *a, const void *b) {
  double _a = *((double *)a);
  double _b = *((double *)b);
  if (((_a < 1 && _a > 0) || (_a > -1 && _a < 0)) &&
      ((_b < 1 && _b > 0) || (_b > -1 && _b < 0))) {
    double d = _a - _b;
    if (d < 0)
      return -1;
    return d == 0 ? 0 : 1;
  }
  return _a - _b;
}
