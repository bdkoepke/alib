#ifndef COLOR_ARRAY_H
#define COLOR_ARRAY_H

#include <stddef.h>

typedef enum {
  Red = 0,
  White = 1,
  Blue = 2
} Color;

const char *color_to_string(const Color);

typedef struct _ColorArray ColorArray;

ColorArray *color_array_new(Color a[], size_t len);

Color color_array_examine(const ColorArray *, size_t);
void color_array_swap(ColorArray *, size_t i, size_t j);
size_t color_array_length(const ColorArray *);

#endif /* COLOR_ARRAY_H */
