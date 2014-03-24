#ifndef ARRAY_H
#define ARRAY_H

#define array_size(a) (sizeof((a)) / sizeof((a)[0]))

void array_puts(int a[], int);

#endif /* ARRAY_H */
