#include "../math.h"
#include "../test.h"
#include "algorithm.h"
#include "array.h"
#include "array_container.h"
#include "binary_tree.h"
#include "stack.h"
#include "test_container.h"
#include "type.h"

#include <stdbool.h>
#include <string.h>

const int test_values[] = { 15, 5, 3, 12, 13, 10, 6, 7, 16, 20, 18, 23 };
const size_t test_values_length = sizeof(test_values) / sizeof(int);
const int test_values_extended[] = {
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
const size_t test_values_extended_length =
    sizeof(test_values_extended) / sizeof(int);

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
  Stack *s = stack_new();
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
}

void question_3_7(void) {
  puts("test_question_3_7");
  BinaryTree *b = binary_tree_new_fast_min_max(compare_int);
  test_dictionary((Dictionary *)b, test_values, test_values_length);
  object_free((Object *)b);
  b = binary_tree_new(compare_int);
  test_dictionary((Dictionary *)b, test_values_extended,
                  test_values_extended_length);
  object_free((Object *)b);
}

void question_3_8(void) { puts("test_question_3_8: not implemented"); }

void question_3_9(void) {
  puts("test_question_3_9");
  BinaryTree *a = binary_tree_new(compare_int);
  BinaryTree *b = binary_tree_new(compare_int);
  size_t i;
  for (i = 0; i < 10; i++)
    container_insert((Container *)a, INT_TO_POINTER(i));
  for (i; i < 20; i++)
    container_insert((Container *)b, INT_TO_POINTER(i));
  BinaryTree *concat = binary_tree_concatenate(a, b);
  for (i = 0; i < 20; i++)
    assert_equals(POINTER_TO_INT(
                      container_search((Container *)concat, INT_TO_POINTER(i))),
                  i);
  object_free((Object *)a);
  object_free((Object *)b);
}

static size_t bin_packing_best_fit(float **w, size_t n) {
  size_t bins = 0;
  BinaryTree *b = binary_tree_new(compare_float);
  size_t i;
  for (i = 0; i < n; i++)
    container_insert((Container *)b, (void *)(w[i]));
}

void question_3_10(void) {
  puts("test_question_3_10: not implemented");
  static float objects[] = {
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
  static const size_t objects_length = 100;

  //printf("%d\n", bin_packing_best_fit((float**)&objects, objects_length));
}

void question_3_11(void) { puts("test_question_3_11: not implemented"); }

void question_3_14(void) { puts("test_question_3_14: not implemented"); }

void question_3_15(void) { puts("test_question_3_15: not implemented"); }

void chapter_3(void) {
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
}
