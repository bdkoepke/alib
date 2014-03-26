#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stddef.h>

#define assert_true(expr)                                                      \
  _assert_true((expr), #expr, __FILE__, __LINE__, __func__)
#define assert_false(expr)                                                     \
  _assert_false((expr), #expr, __FILE__, __LINE__, __func__)
#define assert_equals(a, b)                                                    \
  _assert_equals((a), (b), #a, #b, __FILE__, __LINE__, __func__)
#define assert_not_equals(a, b)                                                \
  _assert_not_equals((a), (b), #a, #b, __FILE__, __LINE__, __func__)

/**
 * Tests whether two memory regions contain the same values.
 *
 * @param a the pointer to the first memory region.
 * @param b the pointer to the second memory region.
 */
#define assert_memcmp(a, b)                                                    \
  _assert_memcmp((a), (b), sizeof(a), #a, #b, __FILE__, __LINE__, __func__)

/**
 * Tests whether two memory regions contain the same values.
 *
 * @param a the pointer to the first memory region.
 * @param b the pointer to the second memory region.
 * @param num the number of bytes to compare.
 */
#define assert_memcmp_len(a, b, num)                                           \
  _assert_memcmp((a), (b), (num), #a, #b, __FILE__, __LINE__, __func__)

void _assert_true(bool expr, const char *expr_s, const char *file, int line,
                  const char *func);
void _assert_false(bool expr, const char *expr_s, const char *file, int line,
                   const char *func);
void _assert_equals(int a, int b, const char *a_s, const char *b_s,
                    const char *file, int line, const char *func);
void _assert_not_equals(int a, int b, const char *a_s, const char *b_s,
                        const char *file, int line, const char *func);
void _assert_memcmp(const void *a, const void *b, size_t num, const char *a_s,
                    const char *b_s, const char *file, int line,
                    const char *func);

#endif /* TEST_H */
