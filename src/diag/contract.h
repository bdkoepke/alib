#ifndef CONTRACT_H
#define CONTRACT_H

#include <stdbool.h>

/**
 * Specifies a precondition that must be true before a function
 * can execute. Should not be compiled out if your deploying a
 * shared library.
 *
 * @param expr the expression to validate.
 */
#define contract_requires(expr)                                                \
  _contract_requires((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies a precondition that must be true before a function
 * can execute. These can be compiled out for performance-critical
 * code and may be expensive to evaluate. For instance, in a data
 * structure you could search to verify that an element exists before
 * trying to delete it. Special care needs to be taken if these are
 * compiled out since they can result in undefined behavior if their
 * contracts are invalidated.
 *
 * @param expr the expression to validate.
 */
#define contract_weak_requires(expr)                                                \
  _contract_weak_requires((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies a condition that must be true after a function executes.
 *
 * @param expr the expression to validate.
 */
#define contract_ensures(expr)                                                 \
  _contract_ensures((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies a condition on an object that must always be true.
 *
 * @param expr the expression to validate.
 */
#define contract_invariant(expr)                                               \
  _contract_invariant((expr), #expr, __FILE__, __LINE__, __func__)


void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);
void _contract_weak_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);
void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func);
void _contract_ensures(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);

#endif /* CONTRACT_H */
