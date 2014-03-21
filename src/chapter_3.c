#include "lang/algorithm.h"
#include "lang/math_extended.h"
#include "lang/sort_int.h"
#include "lang/type.h"
#include "test/test.h"
#include "test/test_container.h"
#include "util/array.h"
#include "util/array_container.h"
#include "util/binary_tree.h"
#include "util/hashtable.h"
#include "util/linked_stack.h"
#include "util/node.h"
#include "util/red_black_tree.h"
#include "util/sparse_array.h"
#include "util/stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const int test_values[] = { 15, 5, 3, 12, 13, 10, 6, 7, 16, 20, 18, 23 };
static const size_t test_values_length = sizeof(test_values) / sizeof(int);
static const int test_values_pre_order[] = { 15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18,
                                      23 };
static const int test_values_in_order[] = { 3, 5, 6, 7, 10, 12, 13, 15, 16, 18, 20,
                                     23 };
static const int test_values_post_order[] = { 3, 7, 6, 10, 13, 12, 5, 18, 23, 20, 16,
                                       15 };
static const int test_values_level_order[] = { 15, 5, 16, 3, 12, 20, 10, 13, 18, 23, 6,
                                        7 };

static const int test_values_extended[] = {
  -670653443, 447976203, 118781771, -199772367, 241648993, 34218826, 603521812,
  372336484, 131490347, 319613229, -471804073, -285454123, 134022543, 656175464,
  -772712535, -587968559, 641680973, -1038659451, 69721356, 177411384,
  -93163603, -1001554245, -912572906, -575237263, -137796943, 755383626,
  328378031, -920076531, -424457714, 578043572, -1033753948, -876715494,
  -842033972, 326494027, 964168059, -1055734510, 570559437, 951850714,
  -1061340436, -740209543, -600428922, -171722683, 920892114, 710989128,
  752657741, -241495629, -428396424, 229412319, -722001722, -971648732,
  666452236, -252063527, -946788131, -872582574, 885662959, 104812679,
  969594726, -92615105, -897287854, -239321228, -693915430, -660124328,
  -947380231, 699087128, -496223854, 695205957, 767783880, -626479261,
  -456258352, 843546071, -844412596, 684297703, 1014217351, -321153750,
  53981536, 850351937, 818089197, -456229060, -990060991, 869537678, 168440527,
  -689362785, 219597497, -793802990, -1000498880, 749747081, 657900506,
  202789524, 526688578, 565167059, -101285015, -945803545, -930791346,
  936350305, -349712959, 737734992, 781253299, -342294642, -760361948,
  825652867, 535856547, -784243723, -976968556, 328103932, 879054071,
  1030071482, -958208909, 791436759, -246261565, -553327129, 1037418698,
  427953598, 3118750, 3949869, 72581032, 582800858, 654223749, -76325020,
  -146797032, 737592843, 1069928612, 746390334, -674251245, -397965185,
  -980666627, -55774029, -245331516, 981466295, -560176724, -1012994359,
  -905289481, 301201198, -159686097, -130182781, -31745796, 247990940,
  -425141829, -861405878, 436228285, -899537536, 344410012, -867270301,
  -257795525, 1041289857, 64678413, 1036908762, 26503555, 57518301, -408849229,
  1014204407, -668811906, 202669354, 220930569, -474803047, 291579559, 32702698,
  411468624, 772972349, 588274557, -277001283, 320617011, 371915747, 455029569,
  -799471981, -500299735, 588119733, -570590794, -944047773, -335423371,
  330193344, 807534990, 216650924, 63624948, -520177135, 400727447, 49999949,
  -1067824977, 677012073, 606876095, 230782695, 418897454, 782031060,
  -360655582, 262119164, 646303546, 47538404, -218416479, 236237381, -49815437,
  799015894, 485523595, 333078963, -1471517, 41048713, 68005459, -300437027,
  827586537, 720191540, -635025321, 839509728, 925700198, -23238628, 32688399,
  164666133, 586595312, 512870444, -76126990, -994239826, -530830954,
  -805538377, -97900355, -300884855, -892756784, -600797973, 720219590,
  -135653103, 769941140, 771457564, -324358422, 1016382028, -772370788,
  -481844222, -571300092, -675230777, -742806532, -361280504, 622555645,
  803140105, 1030900224, -261169209, 249204336, -673319165, 880965695,
  845994344, 83367697, 1061326933, 958269647, 522718910, -236880809, -410196166,
  779077164, -512455103, -860871340, -357158870, 955058242, 761311437,
  -819805816, -603542142, -710893018, 686213743, 961973106, -686687298,
  350244799, -392530031, -642542311
};
static const size_t test_values_extended_length =
    sizeof(test_values_extended) / sizeof(int);

static const int test_values_extended_positive[] = {
  24216, 36783, 17344, 40323, 35826, 253, 46365, 6847, 40026, 7920, 47088,
  34916, 46700, 34675, 40506, 26890, 48707, 54263, 39694, 51446, 46696, 34873,
  64182, 43780, 7589, 20473, 38250, 61898, 40068, 25505, 24680, 16955, 58701,
  59784, 35459, 64343, 9062, 12276, 32841, 61012, 62648, 49210, 14193, 34750,
  39420, 16549, 51958, 5859, 12487, 52354, 7327, 57681, 40374, 32738, 61555,
  59942, 23388, 2060, 57915, 31161, 3705, 33647, 34164, 21307, 23675, 25042,
  57528, 52651, 37312, 37292, 8281, 3421, 43540, 41498, 16078, 51135, 44991,
  22993, 10270, 12681, 46417, 14053, 10941, 50337, 24556, 13576, 46691, 4630,
  20574, 49292, 53050, 50168, 34719, 11129, 49581, 15654, 33340, 15402, 62455,
  42524, 15152, 51169, 6046, 56604, 63752, 16593, 17971, 50899, 49659, 5720,
  35457, 59019, 19429, 10116, 49201, 26137, 36264, 61729, 5909, 26132, 46585,
  3010, 53986, 34163, 25883, 37994, 41459, 33620, 32518, 17424, 4353, 30682,
  59152, 32778, 22338, 32290, 3951, 27601, 24174, 10927, 132, 41793, 56216,
  1350, 14242, 17776, 47842, 60381, 19425, 16236, 16527, 55277, 49260, 31344,
  37880, 31734, 14327, 55887, 57391, 41406, 9828, 41030, 19497, 46084, 37903,
  54839, 44228, 60373, 52578, 13274, 29323, 57219, 50196, 42893, 19831, 10721,
  54602, 15973, 4908, 34048, 51719, 27790, 26414, 29795, 371, 56703, 24571,
  53132, 54961, 23519, 3075, 28308, 1318, 40171, 65448, 51106, 45492, 16780,
  35495, 31850, 49945, 13142, 62054, 6717, 642, 31718, 2125, 11545, 53861,
  21491, 59762, 41709, 25859, 18956, 3834, 60513, 24152, 43053, 63278, 56120,
  46075, 56084, 42728, 51689, 59931, 15205, 64022, 45862, 64410, 36048, 8821,
  45041, 14384, 65051, 19614, 53605, 41284, 64030, 12308, 25076, 28330, 10372,
  36274, 26685, 21388, 58744, 21446, 25902, 42417, 51002, 30778, 16252, 2595,
  30004, 32506
};
static const size_t test_values_extended_positive_length =
    sizeof(test_values_extended_positive) / sizeof(int);

static const double test_bin_packing_values[] = {
  0.3362347542, 0.3178301298, 0.6860678412, 0.7340748264, 0.1900018821,
  0.984185261, 0.0281661723, 0.6661597076, 0.6800948414, 0.7188397606,
  0.0860246283, 0.4094339397, 0.2783007051, 0.6902901942, 0.2631758486,
  0.5286753045, 0.7999930265, 0.7275710572, 0.963349744, 0.2755393689,
  0.5613411679, 0.855369739, 0.1771981616, 0.6169994571, 0.5694481058,
  0.7549725035, 0.8177760153, 0.3599889043, 0.0442691229, 0.9314259891,
  0.4850223095, 0.8299687761, 0.8190858914, 0.1444724957, 0.0456538093,
  0.0205221248, 0.400213286, 0.663251318, 0.4663875755, 0.1214011144,
  0.2012233047, 0.9519117968, 0.7384792918, 0.0222310086, 0.436982126,
  0.3443846819, 0.7886456463, 0.7097351854, 0.0010258025, 0.5920229102,
  0.9021678383, 0.0410867301, 0.422950774, 0.0211955488, 0.8096830852,
  0.9106092143, 0.888359814, 0.375747412, 0.0681978897, 0.7466816537,
  0.4712936091, 0.120154961, 0.2408971242, 0.7367722704, 0.8220452147,
  0.3240947069, 0.682950617, 0.9079132956, 0.4285258572, 0.146888111,
  0.0876527275, 0.0382878911, 0.0445834764, 0.6848543361, 0.4875632254,
  0.9918960403, 0.117704628, 0.9025166214, 0.3724013027, 0.8358311942,
  0.8561985374, 0.5264625514, 0.424305809, 0.3953265098, 0.008127508,
  0.1773252564, 0.5447534164, 0.0778891353, 0.6220337348, 0.5646875447,
  0.4879517267, 0.1906236359, 0.2546306991, 0.4988814902, 0.6807111634,
  0.3669732618, 0.564151499, 0.5531538269, 0.8426301903, 0.6035581056
};
static const size_t test_bin_packing_values_length =
    sizeof(test_bin_packing_values) / sizeof(double);

static bool nested_parenthesis(const char *s, int *count) {
  size_t c = 0;
  size_t i;
  size_t length = strlen(s);
  for (i = 0; i < length; i++) {
    switch (s[i]) {
    case '(':
      c++;
      *count = i;
      break;
    case ')':
      if (c == 0) {
        *count = i;
        return false;
      }
      c--;
      break;
    default:
      continue;
    }
  }

  return c == 0;
}

void _test_array(void) {
  puts("test_array");
  Array *a = array_new();
  test_array(a, test_values, test_values_length);
  object_free((Object *)a);

  a = array_new();
  test_array(a, test_values_extended, test_values_extended_length);
  object_free((Object *)a);
}

void _test_linked_stack(void) {
  puts("test_linked_stack");
  LinkedStack *l = linked_stack_new();
  test_linked_stack(l, test_values, test_values_length);
  object_free((Object *)l);

  l = linked_stack_new();
  test_linked_stack(l, test_values_extended, test_values_extended_length);
  object_free((Object *)l);
}

void _test_queue(void) {
  puts("test_queue");
  Queue *q = queue_new();
  test_queue(q, test_values, test_values_length);
  object_free((Object *)q);

  q = queue_new();
  test_queue(q, test_values_extended, test_values_extended_length);
  object_free((Object *)q);
}

void test_binary_tree(void) {
  puts("test_binary_tree");
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  test_tree((Tree *)b, test_values, test_values_length, test_values_pre_order,
            test_values_in_order, test_values_post_order,
            test_values_level_order);
  object_free((Object *)b);

  b = binary_tree_new(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void test_red_black_tree(void) {
  puts("test_red_black_tree: not implemented");
  /*  Tree *r = red_black_tree_new(compare_int_pointer);
    test_tree((Tree *)r, test_values, test_values_length, test_values_pre_order,
              test_values_in_order, test_values_post_order,
              test_values_level_order);
    object_free((Object *)r);
  
    r = red_black_tree_new(compare_int_pointer);
    test_dictionary((Dictionary *)r, test_values_extended,
                    test_values_extended_length);
    object_free((Object *)r); */
}

void test_hashtable(void) {
  puts("test_hashtable");
  Container *c = hashtable_new(hash_int_pointer);
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);

  c = hashtable_new(hash_int_pointer);
  test_container(c, test_values_extended, test_values_extended_length);
  object_free((Object *)c);
}

void question_3_1(void) {
  puts("test_question_3_1");
  int count;
  assert_true(nested_parenthesis("((())())()", &count));
  assert_false(nested_parenthesis(")()(", &count));
  assert_equals(count, 0);
  assert_false(nested_parenthesis("()(", &count));
  assert_equals(count, 2);
}

void question_3_2(void) {
  puts("test_question_3_2");
  Stack *s = (Stack *)linked_stack_new();
  test_stack(s, test_values, test_values_length);
  test_stack(s, test_values_extended, test_values_extended_length);
  object_free((Object *)s);
}

void question_3_3(void) {
  puts("test_question_3_3");
  Array *a = array_new();
  test_container((Container *)a, test_values, test_values_length);
  object_free((Object *)a);
  a = array_new();
  test_container((Container *)a, test_values_extended,
                 test_values_extended_length);
  object_free((Object *)a);
}

void question_3_4(void) {
  puts("test_question_3_4");
  Container *c = (Container *)array_container_new(
      reduce_int(test_values, test_values_length, max, 0));
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);
  c = (Container *)array_container_new(
      reduce_int(test_values_extended_positive,
                 test_values_extended_positive_length, max, 0));
  test_container(c, test_values_extended_positive,
                 test_values_extended_positive_length);
  object_free((Object *)c);
}

void question_3_7(void) {
  puts("test_question_3_7");
  BinaryTree *b = binary_tree_new_fast_min_max(compare_int_pointer);
  test_tree((Tree *)b, test_values, test_values_length, test_values_pre_order,
            test_values_in_order, test_values_post_order,
            test_values_level_order);
  object_free((Object *)b);

  b = binary_tree_new_fast_min_max(compare_int_pointer);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void question_3_8(void) {
  puts("test_question_3_8: partial implementation");
  /*
   SortedSet *s = sorted_set_new(compare_int_pointer);
   test_sorted_set(s, test_values, test_values_length);
   object_free((Object *)s);
 
   s = sorted_set_new(compare_int_pointer);
   test_sorted_set(s, test_values_extended, test_values_extended_length);
   object_free((Object *)s);
 	*/
}

void question_3_9(void) {
  puts("test_question_3_9");
  BinaryTree *a = binary_tree_new(compare_int_pointer);
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < 10; i++)
    container_insert((Container *)a, INT_TO_POINTER(i));
  for (i; i < 20; i++)
    container_insert((Container *)b, INT_TO_POINTER(i));
  BinaryTree *concat = binary_tree_concat(a, b);
  for (i = 0; i < 20; i++)
    assert_equals(POINTER_TO_INT(
                      container_search((Container *)concat, INT_TO_POINTER(i))),
                  i);
  object_free((Object *)concat);
}

static size_t bin_packing_best_fit(const double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, (void *)&w[i]);

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    double r = 1.0 - bin;
    double *predecessor = (double *)dictionary_predecessor((Dictionary *)b, &r);
    if (predecessor == NULL) {
      bins++;
      bin = 0;
    } else {
      bin += *predecessor;
      container_delete((Container *)b, predecessor);
    }
  }
  object_free((Object *)b);
  return bin == 0 ? bins : bins + 1;
}

static size_t bin_packing_worst_fit(const double *w, size_t n) {
  BinaryTree *b = binary_tree_new(compare_double);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, (void *)&w[i]);

  size_t bins = 0;
  double bin = 0;
  while (!container_empty((Container *)b)) {
    double *min = (double *)dictionary_min((Dictionary *)b);
    if (*min > (1 - bin)) {
      bins++;
      bin = 0;
    } else {
      bin += *min;
      container_delete((Container *)b, min);
    }
  }
  object_free((Object *)b);
  return bin == 0 ? bins : bins + 1;
}

void question_3_10(void) {
  puts("test_question_3_10");
  assert_equals(bin_packing_worst_fit(test_bin_packing_values,
                                      test_bin_packing_values_length),
                63);
  assert_equals(bin_packing_best_fit(test_bin_packing_values,
                                     test_bin_packing_values_length),
                52);
}

void question_3_11(void) {
  puts("test_question_3_11: partial implementation");
  /*
   RangeContainer *r = array_range_container_new(compare_int_pointer);
   test_range_container(r, test_values, test_values_length);
   object_free((Object *)r);
 
   r = array_range_container_new(compare_int_pointer);
   test_range_container(r, test_values_extended, test_values_extended_length);
   object_free((Object *)r);
 	*/
}

void question_3_14(void) {
  puts("test_question_3_14: not implemented");
  PartialSum *p = partial_sum_new(compare_int_pointer);
  test_partial_sum(p, test_values, test_values_length);
  object_free((Object *)p);

  p = partial_sum_new(compare_int_pointer);
  test_partial_sum(p, test_values_extended, test_values_extended_length);
  object_free((Object *)p);
}

void question_3_15(void) {
  puts("test_question_3_15");
  Container *c =
      sparse_array_new(reduce_int(test_values, test_values_length, max, 0) + 1,
                       test_values_length);
  test_container(c, test_values, test_values_length);
  object_free((Object *)c);

  c = sparse_array_new(
      reduce_int(test_values_extended_positive,
                 test_values_extended_positive_length, max, 0) + 1,
      test_values_extended_positive_length);
  test_container(c, test_values_extended_positive,
                 test_values_extended_positive_length);
  object_free((Object *)c);
}

void question_3_20(void) {
  puts("test_question_3_20");
  // completed in test_linked_stack
}

void question_3_21(void) {
  puts("test_question_3_21");
  BinaryTree *a = binary_tree_new(compare_int_pointer);
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < test_values_length - 1; i++) {
    container_insert((Container *)a, INT_TO_POINTER(test_values[i]));
    container_insert((Container *)b, INT_TO_POINTER(test_values[i]));
  }
  assert_true(binary_tree_compare(a, b));

  container_insert((Container *)a, INT_TO_POINTER(test_values[i]));
  assert_false(binary_tree_compare(a, b));

  object_free((Object *)a);
  object_free((Object *)b);
}

static void linked_stack_visitor(void *p, void *x) {
  stack_push((Stack *)p, x);
}

void question_3_22(void) {
  puts("test_question_3_22");
  BinaryTree *b = binary_tree_new(compare_int_pointer);
  size_t i;
  for (i = 0; i < test_values_length; i++)
    container_insert((Container *)b, INT_TO_POINTER(test_values[i]));

  LinkedStack *l = tree_to_linked_stack((Tree *)b);

  assert_false(container_empty((Container *)l));
  int j;
  for (j = (test_values_length - 1); j >= 0; j--)
    assert_equals(POINTER_TO_INT(stack_pop((Stack *)l)),
                  test_values_in_order[j]);
  assert_true(container_empty((Container *)l));
}

void question_3_23(void) {
  puts("test_question_3_23");
  // completed in test_linked_stack
}

static char *reverse_line(const char *line, size_t length) {
  char *reverse = malloc(sizeof(char) * length + 1);
  reverse[length] = '\0';
  size_t i;
  size_t j = 0;
  for (i = j = 0; i <= length; i++) {
    switch (line[i]) {
    case ' ':
      reverse[length - i - 1] = ' ';
    case '\0':
      ; // empty statement
      size_t word_len = i - j;
      memcpy(&reverse[length - i], &line[j], sizeof(char) * word_len);
      j = i + 1;
      break;
    default:
      break;
    }
  }
  return reverse;
}

void question_3_26(void) {
  puts("test_question_3_26");
  static const char *line = "My name is Chris";
  static const char *line_reversed = "Chris is name My";
  char *reverse = reverse_line(line, strlen(line));
  size_t i;
  for (i = 0; i <= strlen(line); i++)
    assert_equals(reverse[i], line_reversed[i]);
}

void question_3_27(void) {
  puts("test_question_3_27");
  Node *head = node_new_leaf(INT_TO_POINTER(0));
  Node *node = head;
  size_t i;
  for (i = 1; i < 6; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  Node *loop = node;
  for (i = 6; i < 9; i++) {
    Node *next = node_new_leaf(INT_TO_POINTER(i));
    node->n = next;
    node = next;
  }
  node->n = loop;

  assert_equals(node_loop(head), 6);
}

static int *unordered_product_ignoring_index_with_division(const int *X,
                                                           size_t length) {
  int *M = malloc(sizeof(int) * length);
  size_t i;
  int r = 1;
  for (i = 0; i < length; i++)
    r *= X[i];
  for (i = 0; i < length; i++)
    M[i] = r / X[i];
  return M;
}

static int *unordered_product_ignoring_index(const int *X, size_t length) {
  int number_of_products = log2(length);
  int *Y = malloc(sizeof(int) * length);
  int *M = malloc(sizeof(int) * length);
  Y = memcpy(Y, X, sizeof(int) * length);
  size_t i, j;
  for (i = 0; i < length; i++)
    for (j = 1; j < number_of_products; j++)
      Y[i] *= X[(i + j) % length];
  for (i = 0; i < length; i++) {
    M[i] = Y[(i + 1) % length];
    for (j = 1; j < (number_of_products - 1); j++)
      M[i] *= Y[(i + (j * number_of_products) + 1) % length];
    M[i] *= X[(i + (j * number_of_products) + 1) % length];
  }
  free(Y);
  return M;
}

static void test_unordered_product_ignoring_index(const int *X, size_t length) {
  int *actual = unordered_product_ignoring_index(X, length);
  size_t i;
  int *expected = unordered_product_ignoring_index_with_division(X, length);
  for (i = 0; i < length; i++)
    assert_equals(actual[i], expected[i]);
  free(actual);
  free(expected);
}

void question_3_28(void) {
  puts("test_question_3_28");
  static int unordered[] = { 6, 5, 3, 1, 7, 6, 2, 3 };
  static size_t unordered_length = sizeof(unordered) / sizeof(int);
  test_unordered_product_ignoring_index(unordered, unordered_length);
}
