#include "chapter_2.h"
#include "chapter_3.h"
#include "chapter_4.h"

void chapter_2(void) {
  test_selectionsort();
  test_insertionsort();
  test_find_match();
  test_power();
}

void chapter_3(void) {
  _test_array();
  _test_linked_stack();
  _test_queue();
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
	_test_heap();
	test_mergesort();
	test_quicksort();
}

int main(void) {
  chapter_2();
  chapter_3();
  chapter_4();
}
