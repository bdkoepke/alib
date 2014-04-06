#include "chapter_2.h"
#include "chapter_3.h"
#include "chapter_4.h"
#include "chapter_5.h"

void chapter_2(void) {
  test_selectionsort();
  test_insertionsort();
  test_find_match();
  test_power();
}

void chapter_3(void) {
  _test_array_list();
  _test_linked_stack();
  test_linked_queue();
  test_binary_tree();
  test_red_black_tree();
  test_hashtable();
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
  question_3_8();
  question_3_9();
  question_3_10();
  question_3_11();
  question_3_14();
  question_3_15();
  question_3_20();
  question_3_21();
  question_3_22();
  question_3_23();
  question_3_26();
  question_3_27();
  question_3_28();
}

void chapter_4(void) {
  test_max_min();
  _test_heap();
  test_binary_search();
  test_count_occurrences();
  test_mergesort();
  test_quicksort();
  test_sqrt();
  test_bucketsort();
  question_4_1();
  question_4_2();
  question_4_3();
  question_4_4();
  question_4_5();
  question_4_6();
  question_4_8();
  question_4_9();
  question_4_10();
  question_4_11();
  question_4_12();
  question_4_14();
  question_4_15();
  question_4_16();
  question_4_18();
  question_4_20();
  question_4_23();
  question_4_24();
  question_4_25();
  question_4_26();
  question_4_27();
  question_4_31();
  question_4_33();
  question_4_34();
  question_4_35();
  question_4_45();
  question_4_46();
}

void chapter_5(void) { test_linked_graph(); }

int main(void) {
  chapter_2();
  chapter_3();
  chapter_4();
  chapter_5();
}
