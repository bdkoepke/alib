#ifndef CONTAINER_TEST_H
#define CONTAINER_TEST_H

#include "array.h"
#include "container.h"
#include "dictionary.h"
#include "graph.h"
#include "priority_queue.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

void test_array(Array *, const int *, size_t);
void test_container(Container *, const int *, size_t);
void test_dictionary(Dictionary *, const int *, size_t);
void test_graph(Graph *, const int *, size_t);
void test_priority_queue(PriorityQueue *, const int *, size_t);
void test_queue(Queue *, const int *, size_t);
void test_stack(Stack *, const int *, size_t);
void test_tree(Tree *, const int *, size_t);

#endif /* CONTAINER_TEST_H */
