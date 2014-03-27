#include "../diag/contract.h"
#include "../lang/math_extended.h"
#include "range_container.h"

#include <stdlib.h>
#include <stdint.h>

typedef struct {
  range_container_vtable *vtable;
  size_t size;
  size_t capacity;
  Compare c;
  void **m;
} ArrayRangeContainer;

static const int DEFAULT_CAPACITY = 11;

static void array_range_container_insert(RangeContainer *r, void *x) {
  ArrayRangeContainer *a = (ArrayRangeContainer *)r;
  if (a->size >= a->capacity) {
    size_t _capacity =
        checked_product(a->capacity * sizeof(void *), 2, SIZE_MAX);
    a->m = realloc(a->m, _capacity);
    a->capacity = _capacity / sizeof(void *);
  }
  size_t i, j, capacity;
  void **m = a->m;
  size_t size = a->size;

  /*
  	a->size++;
  	for (i = 0; i < size; i++) {
  		void *min = m[0][size];
  		for (j = 1; j < size; j++)
  			if (a->c(min, m[i][j]) < 0)
  				min = m[i][j];
  		m[i][size] = min;
  	}
 	*/
}

static void *array_range_container_query(const RangeContainer *r, size_t i,
                                         size_t j) {
  return NULL;
}

static void array_range_container_free(Object *o) { free(o); }

RangeContainer *array_range_container_new(Compare c) {
  static range_container_vtable vtable = {
    {.free = array_range_container_free },
        .insert = array_range_container_insert, .query =
                                                    array_range_container_query
  };

  ArrayRangeContainer *r = malloc(sizeof(ArrayRangeContainer *));
  r->vtable = &vtable;
  r->capacity = DEFAULT_CAPACITY;
  r->size = 0;
  r->c = c;
  r->m = malloc(sizeof(void *) * square(r->capacity));
  return (RangeContainer *)r;
}

void range_container_insert(RangeContainer *r, void *x) {
  contract_requires(r != NULL && x != NULL);
  r->vtable->insert(r, x);
}

void *range_container_query(const RangeContainer *r, size_t i, size_t j) {
  contract_requires(r != NULL && i <= j);
  return r->vtable->query(r, i, j);
}
