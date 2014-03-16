#include "../test.h"
#include "array.h"
#include "array_container.h"
#include "binary_tree.h"
#include "stack.h"
#include "type.h"

#include <stdbool.h>
#include <string.h>

const int test_values[] = { 15, 5, 3, 12, 13, 10, 6, 7, 16, 20, 18, 23 };
const size_t test_values_length = sizeof(test_values) / sizeof(int);
const int test_values_extended[] = {
  -1341306887, 895952407, 237563543, -399544734, 483297986, 68437652,
  1207043625, 744672968, 262980695, 639226459, -943608147, -570908247,
  268045087, 1312350929, -1545425070, -1175937119, 1283361946, -2077318902,
  139442713, 354822769, -186327206, -2003108490, -1825145812, -1150474526,
  -275593886, 1510767253, 656756062, -1840153062, -848915429, 1156087144,
  -2067507897, -1753430989, -1684067944, 652988055, 1928336118, -2111469021,
  1141118875, 1903701428, -2122680872, -1480419087, -1200857845, -343445367,
  1841784229, 1421978256, 1505315482, -482991259, -856792848, 458824638,
  -1444003444, -1943297464, 1332904473, -504127054, -1893576263, -1745165149,
  1771325919, 209625358, 1939189453, -185230211, -1794575709, -478642457,
  -1387830860, -1320248656, -1894760462, 1398174257, -992447709, 1390411914,
  1535567760, -1252958522, -912516704, 1687092143, -1688825192, 1368595407,
  2028434703, -642307500, 107963073, 1700703875, 1636178395, -912458120,
  -1980121982, 1739075356, 336881055, -1378725570, 439194995, -1587605981,
  -2000997761, 1499494162, 1315801013, 405579049, 1053377156, 1130334119,
  -202570031, -1891607090, -1861582693, 1872700611, -699425919, 1475469984,
  1562506598, -684589285, -1520723897, 1651305735, 1071713094, -1568487447,
  -1953937112, 656207865, 1758108142, 2060142964, -1916417818, 1582873518,
  -492523130, -1106654258, 2074837397, 855907197, 6237500, 7899738, 145162064,
  1165601716, 1308447499, -152650041, -293594065, 1475185686, 2139857224,
  1492780669, -1348502490, -795930370, -1961333254, -111548058, -490663032,
  1962932591, -1120353449, -2025988719, -1810578962, 602402397, -319372195,
  -260365562, -63491592, 495981880, -850283658, -1722811757, 872456571,
  -1799075072, 688820025, -1734540603, -515591050, 2082579715, 129356826,
  2073817525, 53007110, 115036602, -817698459, 2028408815, -1337623812,
  405338709, 441861138, -949606094, 583159118, 65405396, 822937249, 1545944699,
  1176549115, -554002566, 641234023, 743831495, 910059139, -1598943962,
  -1000599470, 1176239467, -1141181588, -1888095547, -670846743, 660386689,
  1615069981, 433301849, 127249896, -1040354271, 801454895, 99999898,
  -2135649955, 1354024146, 1213752190, 461565390, 837794909, 1564062121,
  -721311165, 524238328, 1292607092, 95076808, -436832959, 472474762, -99630875,
  1598031789, 971047191, 666157927, -2943035, 82097426, 136010919, -600874055,
  1655173074, 1440383081, -1270050643, 1679019456, 1851400397, -46477257,
  65376799, 329332267, 1173190624, 1025740888, -152253981, -1988479653,
  -1061661909, -1611076755, -195800711, -601769710, -1785513568, -1201595946,
  1440439180, -271306207, 1539882280, 1542915128, -648716845, 2032764057,
  -1544741577, -963688444, -1142600185, -1350461554, -1485613065, -722561009,
  1245111290, 1606280210, 2061800449, -522338419, 498408672, -1346638330,
  1761931390, 1691988689, 166735395, 2122653866, 1916539295, 1045437821,
  -473761618, -820392332, 1558154328, -1024910206, -1721742680, -714317741,
  1910116485, 1522622874, -1639611633, -1207084284, -1421786036, 1372427486,
  1923946213, -1373374596, 700489599, -785060063, -1285084623,
};
const size_t test_values_extended_length = sizeof(test_values_extended) / sizeof(int);

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
  Array *array = array_new();
  size_t i;
  for (i = 0; i < 100; i++) {
    container_insert((Container *)array, INT_TO_POINTER(i));
    assert_equals(POINTER_TO_INT(array_get(array, i)), i);
  }
  for (i = 99; i > 0; i--) {
    size_t j = i - 1;
    container_delete((Container *)array, INT_TO_POINTER(j));
    assert_equals(
        POINTER_TO_INT(container_search((Container *)array, INT_TO_POINTER(j))),
        0);
  }

  object_free((Object *)array);
}

void question_3_4(void) {
  puts("test_question_3_4");
  Container *c = array_container_new(test_values_length);
	test_container(c, test_values, test_values_length);
  object_free((Object *)c);
  c = array_container_new(test_values_length);
	test_container(c, test_values_extended, test_values_extended_length);
  object_free((Object *)c);
}

void question_3_7(void) {
  puts("test_question_3_7");
  BinaryTree *b = binary_tree_new(compare_int);
	test_container((Container *)b, test_values, test_values_length);
	test_container((Container *)b, test_values_extended, test_values_extended_length);
  object_free((Object *)b);
}

void chapter_3(void) {
  question_3_1();
  question_3_2();
  question_3_3();
  question_3_4();
  question_3_7();
}
