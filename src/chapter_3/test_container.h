#ifndef TEST_CONTAINER_H
#define TEST_CONTAINER_H

#include "array.h"
#include "container.h"
#include "dictionary.h"
#include "graph.h"
#include "partial_sum.h"
#include "priority_queue.h"
#include "queue.h"
#include "range_container.h"
#include "sorted_set.h"
#include "stack.h"
#include "tree.h"

void test_array(Array *, const int *, size_t);
void test_container(Container *, const int *, size_t);
void test_dictionary(Dictionary *, const int *, size_t);
void test_graph(Graph *, const int *, size_t);
void test_partial_sum(PartialSum *, const int *, size_t);
void test_priority_queue(PriorityQueue *, const int *, size_t);
void test_queue(Queue *, const int *, size_t);
void test_range_container(RangeContainer *, const int *, size_t);
void test_sorted_set(SortedSet *, const int *, size_t);
void test_stack(Stack *, const int *, size_t);
void test_tree(Tree *, const int *, size_t, const int *pre_order,
               const int *in_order, const int *post_order,
               const int *level_order);

#endif /* TEST_CONTAINER_H */
