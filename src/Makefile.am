AM_CFLAGS = $(ALIB_CFLAGS)\
  -Wall\
  -Werror\
  -Wextra\
  -Wunused-function\
  -std=c11\
  -pedantic-errors\
  -g

bin_PROGRAMS = alib

alib_SOURCES =\
  chapter_4.c\
  chapter_2.c\
  chapter_3.c\
  diag/contract.c\
  lang/algorithm.c\
  lang/array.c\
  lang/hash.c\
  lang/math_extended.c\
  lang/object.c\
  lang/sort.c\
  lang/sort_int.c\
  lang/string.c\
  main.c\
  test/test.c\
  test/test_container.c\
  test/test_container_values.c\
  test/test_sort.c\
  util/array_container.c\
  util/array_list.c\
  util/binary_node.c\
  util/binary_tree.c\
  util/compare.c\
  util/container.c\
  util/dictionary.c\
  util/hashtable.c\
  util/heap.c\
  util/iterator.c\
  util/linked_stack.c\
  util/node.c\
  util/partial_sum.c\
  util/priority_queue.c\
  util/queue.c\
  util/range_container.c\
  util/red_black_tree.c\
  util/sorted_set.c\
  util/sparse_array.c\
  util/stack.c\
  util/tree.c

alib_CFLAGS = $(ALIB_CFLAGS)

alib_LDFLAGS = -lm

alib_LDADD = $(ALIB_LIBS)
