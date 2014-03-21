#ifndef TEST_CONTAINER_H
#define TEST_CONTAINER_H

#include "../util/array.h"
#include "../util/container.h"
#include "../util/dictionary.h"
#include "../util/graph.h"
#include "../util/linked_stack.h"
#include "../util/partial_sum.h"
#include "../util/priority_queue.h"
#include "../util/queue.h"
#include "../util/range_container.h"
#include "../util/sorted_set.h"
#include "../util/stack.h"
#include "../util/tree.h"

void test_array(Array *, const int *, size_t);
void test_container(Container *, const int *, size_t);
void test_dictionary(Dictionary *, const int *, size_t);
void test_graph(Graph *, const int *, size_t);
void test_linked_stack(LinkedStack *, const int *, size_t);
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
