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
 * Specifies that them specified parameter must not be null before
 * a function can execute. Should not be compiled out if you are
 * deploying a shared library.
 *
 * @param x the value to test for null.
 * @return a pointer to the value.
 */
#define contract_requires_non_null(x)                                          \
  _contract_requires_non_null((x), #x, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified values must be equal before a function executes.
 *
 * @param a the first value.
 * @param b the second value.
 * @return the first value.
 */
#define contract_requires_equal(a, b)                                          \
  _contract_requires_equal((a), (b), #a, #b, __FILE__, __LINE__, __func__)

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
#define contract_weak_requires(expr)                                           \
  _contract_requires((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies that them specified parameter must not be null before
 * a function can execute. Should not be compiled out if you are
 * deploying a shared library.
 *
 * @param x the value to test for null.
 * @return a pointer to the value.
 */
#define contract_weak_requires_non_null(x)                                     \
  _contract_requires_non_null((x), #x, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified values must be equal before a function executes.
 *
 * @param a the first value.
 * @param b the second value.
 * @return the first value.
 */
#define contract_weak_requires_equal(a, b)                                     \
  _contract_requires_equal((a), (b), #a, #b, __FILE__, __LINE__, __func__)

/**
 * Specifies a condition that must be true after a function executes.
 *
 * @param expr the expression to validate.
 */
#define contract_ensures(expr)                                                 \
  _contract_ensures((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified value must not be null after a function
 * executes.
 *
 * @param x the value to test for null.
 * @return a pointer to the value.
 */
#define contract_ensures_non_null(x)                                           \
  _contract_ensures_non_null((x), #x, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified values must be equal after a function executes.
 *
 * @param a the first value.
 * @param b the second value.
 * @return the first value.
 */
#define contract_ensures_equal(a, b)                                           \
  _contract_ensures_equal((a), (b), #a, #b, __FILE__, __LINE__, __func__)

/**
 * Specifies a condition that must be true after a function executes.
 *
 * @param expr the expression to validate.
 */
#define contract_weak_ensures(expr)                                            \
  _contract_ensures((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified value must not be null after a function
 * executes.
 *
 * @param x the value to test for null.
 * @return a pointer to the value.
 */
#define contract_weak_ensures_non_null(x)                                      \
  _contract_ensures_non_null((x), #x, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified values must be equal after a function executes.
 *
 * @param a the first value.
 * @param b the second value.
 * @return the first value.
 */
#define contract_weak_ensures_equal(a, b)                                      \
  _contract_ensures_equal((a), (b), #a, #b, __FILE__, __LINE__, __func__)

/**
 * Specifies a condition on an object that must always be true.
 *
 * @param expr the expression to validate.
 */
#define contract_invariant(expr)                                               \
  _contract_invariant((expr), #expr, __FILE__, __LINE__, __func__)
/**
 * Specifies that the specified value can never be null.
 *
 * @param x the value to test for null.
 * @return a pointer to the value.
 */
#define contract_invariant_non_null(x)                                         \
  _contract_invariant_non_null((x), #x, __FILE__, __LINE__, __func__)

void _contract_requires(bool expr, const char *expr_s, const char *file,
                        int line, const char *func);
void *_contract_requires_non_null(const void *x, const char *x_s,
                                  const char *file, int line, const char *func);
void *_contract_requires_equal(const void *a, const void *b, const char *a_s,
                               const char *b_s, const char *file, int line,
                               const char *func);

void _contract_invariant(bool expr, const char *expr_s, const char *file,
                         int line, const char *func);
void *_contract_invariant_non_null(const void *x, const char *x_s,
                                   const char *file, int line,
                                   const char *func);

void _contract_ensures(bool expr, const char *expr_s, const char *file,
                       int line, const char *func);
void *_contract_ensures_non_null(const void *x, const char *x_s,
                                 const char *file, int line, const char *func);
void *_contract_ensures_equal(const void *a, const void *b, const char *a_s,
                              const char *b_s, const char *file, int line,
                              const char *func);

#endif /* CONTRACT_H */
