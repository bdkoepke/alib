#include "../diag/contract.h"
#include "../lang/object.h"
#include "color_array.h"

#include <stdlib.h>

struct _ColorArray {
	object_vtable *vtable;
	Color *a;
	size_t len;
};

const char *color_to_string(const Color c) {
	switch (c) {
		case Red:
			return "Red";
		case White:
			return "White";
		case Blue:
			return "Blue";
	}
}

ColorArray *color_array_new(Color a[], size_t len) {
	static object_vtable vtable = {
		.free = _object_free
	};

	contract_requires(a != NULL);
	ColorArray *c = malloc(sizeof(ColorArray));
	c->a = a;
	c->len = len;
	c->vtable = &vtable;
	return c;
}

Color color_array_examine(const ColorArray *c, size_t i) {
	contract_requires(c != NULL && i < c->len);
	return c->a[i];
}

void color_array_swap(ColorArray *c, size_t i, size_t j) {
	contract_requires(c != NULL && i < c->len && j < c->len);
	Color t = c->a[i];
	c->a[i] = c->a[j], c->a[j] = t;
}

size_t color_array_length(const ColorArray *c) {
	contract_requires(c != NULL);
	return c->len;
}
