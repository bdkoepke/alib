#ifndef CONTRACT_H
#define CONTRACT_H

#include <stdbool.h>

#define contract_ensures(expr)                                                 \
  _contract_ensures((expr), #expr, __FILE__, __LINE__, __func__)
#define contract_invariant(expr)                                               \
  _contract_invariant((expr), #expr, __FILE__, __LINE__, __func__)
#define contract_requires(expr)                                                \
  _contract_requires((expr), #expr, __FILE__, __LINE__, __func__)

void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);
void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func);
void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);

#endif /* CONTRACT_H */
