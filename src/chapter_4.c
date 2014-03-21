#include "chapter_4.h"
#include "test/test_container.h"
#include "test/test_container_values.h"
#include "util/compare.h"

void _test_heap(void) {
  puts("test_heap");
  Heap *h = heap_new(compare_int_pointer);
  test_heap(h, test_values, test_values_length);
  object_free((Object *)h);

  h = heap_new(compare_int_pointer);
  test_heap(h, test_values_extended, test_values_extended_length);
  object_free((Object *)h);
}
