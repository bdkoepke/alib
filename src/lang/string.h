#ifndef STRING_H
#define STRING_H

/**
 * Finds a pattern in the text.
 *
 * @param pattern the pattern to search for
 * @param text the text to search in
 * @param m the length of pattern
 * @param n the length of the text
 * @return the index of the match in the text,
 * -1 if there is no match.
 */
int find_match(const char *pattern, const char *text, int m, int n);

#endif /* STRING_H */
