#ifndef COMPARE_H
#define COMPARE_H

typedef int (*Compare)(const void *, const void *);

extern int compare_int(const void *, const void *);

#endif /* COMPARE_H */
