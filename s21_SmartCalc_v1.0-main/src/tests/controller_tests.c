/* created by sheritsh // Oleg Polovinko ※ School 21, Kzn */

#include "controller_tests.h"

/*  TEST OPTIONS */

START_TEST(api_calc_opt_1) {
  char *input = "5+10+97+0log(12)";
  long double res = 0;
  api_calculate_str(input, &res);
  ck_assert_ldouble_eq(res, 112.000000);
}
END_TEST

START_TEST(api_calc_opt_2) {
  char *input = "2^2^3";
  long double res = 0;
  api_calculate_str(input, &res);
  ck_assert_ldouble_eq(res, 256.000000);
}
END_TEST

START_TEST(api_calc_opt_3) {
  char *input = "acos(15)+asin(30)/(atan(2)*sqrt(9))";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (-0.308071)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_4) {
  char *input = "cos(3-1)/sin(5)*tan(1)^1";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (-0.420225)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_5) {
  char *input = "mod(2+2)-(-1)";
  long double res = 0;
  api_calculate_str(input, &res);
  ck_assert_ldouble_eq(res, 5.000000);
}
END_TEST

START_TEST(api_calc_opt_6) {
  char *input =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (-30.0722)) < 1e-4 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_7) {
  char *input = "cos(3-1)/sin(5)*tan(1)^1";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (-0.420225)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_8) {
  char *input = "1e5+1e+4/1e-1";
  long double res = 0;
  api_calculate_str(input, &res);
  ck_assert_ldouble_eq(res, 200000.000000);
}
END_TEST

START_TEST(api_calc_opt_9) {
  char *input = "ln(10)-(-log(2))";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (2.33224)) < 1e-4 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_10) {
  char *input = "acos(6)+asin(9)/atan(0.5)+sqrt(1e-1)";
  long double res = 0;
  api_calculate_str(input, &res);
  int test_res = fabsl(res - (0.858795)) < 1e-6 ? OK : FAILURE;
  ck_assert_ldouble_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_opt_11) {
  char *input = "pussy_test";
  long double res = 0;
  int res_test = api_calculate_str(input, &res);
  ck_assert_int_eq(res_test, FAILURE);
}
END_TEST

START_TEST(api_calc_opt_12) {
  char *input = "(cos(()))";
  long double res = 0;
  int res_test = api_calculate_str(input, &res);
  ck_assert_int_eq(res_test, FAILURE);
}
END_TEST

START_TEST(api_calc_with_x_opt_1) {
  char *input = "xxx";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  ck_assert_ldouble_eq(res, -8.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_2) {
  char *input = "cos(3-1)/sin(5)*tan(1)^1x";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (-0.420654)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_3) {
  char *input = "acos(6)+asin(9)/atan(0.5x)+sqrt(1e-1)";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (0.754673)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_4) {
  char *input = "ln(10)-(-log(2xx))";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (2.389046)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_5) {
  char *input = "ln(10xx)-x(-log(2))";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (3.673714)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_6) {
  char *input = "1e5+1e+4/1e-1x";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  ck_assert_ldouble_eq(res, -100000.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_7) {
  char *input = "12031997+05101997";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  ck_assert_ldouble_eq(res, 17133994.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_8) {
  char *input = "x+5";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (3)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_9) {
  char *input = "1e+6-x";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  ck_assert_ldouble_eq(res, 1000002.000000);
}
END_TEST

START_TEST(api_calc_with_x_opt_10) {
  char *input = "sin(130)+x-xx(x)";
  long double res = 0;
  api_calculate_str_with_x(input, -2, &res);
  int test_res = fabsl(res - (-0.790433)) < 1e-4 ? OK : FAILURE;
  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(api_calc_with_x_opt_11) {
  char *input = "sin)";
  long double res = 0;
  int test_res = api_calculate_str_with_x(input, -2, &res);
  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(api_calc_with_x_opt_12) {
  char *input = "all_gonna_be_ok!";
  long double res = 0;
  int test_res = api_calculate_str_with_x(input, -2, &res);
  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(api_infix_to_postfix_opt_1) {
  char *input = "sin(130)";
  char res[510] = {'\0'};
  api_infix_to_postfix_notation(input, res);
  ck_assert_str_eq(res, "130 sin ");
}
END_TEST

START_TEST(api_infix_to_postfix_opt_2) {
  char *input = "7777+77777-66666666999999999^4^2-896";
  char res[510] = {'\0'};
  api_infix_to_postfix_notation(input, res);
  ck_assert_str_eq(res, "7777 77777 + 66666666999999999 4 2 ^ ^ - 896 - ");
}
END_TEST

START_TEST(api_infix_to_postfix_opt_3) {
  char *input = "acos(15)+asin(30)/(atan(2)*sqrt(9))";
  char res[510] = {'\0'};
  api_infix_to_postfix_notation(input, res);
  ck_assert_str_eq(res, "15 30 2 9 sqrt * atan / asin + acos ");
}
END_TEST

START_TEST(api_infix_to_postfix_opt_4) {
  char *input = "1e5+1e+4/1e-1";
  char res[510] = {'\0'};
  api_infix_to_postfix_notation(input, res);
  ck_assert_str_eq(res, "1e5 1e+4 1e-1 / + ");
}
END_TEST

START_TEST(api_infix_to_postfix_opt_5) {
  char *input = "// sheritsh // dream of californication";
  char res[510] = {'\0'};
  int res_test = api_infix_to_postfix_notation(input, res);
  ck_assert_int_eq(res_test, FAILURE);
}
END_TEST

/*  TEST SUITES */

Suite *api_calc_suit(void) {
  Suite *suite = suite_create("api_calc");
  TCase *tc_core = tcase_create("core_of_api_calc");
  tcase_add_test(tc_core, api_calc_opt_1);
  tcase_add_test(tc_core, api_calc_opt_2);
  tcase_add_test(tc_core, api_calc_opt_3);
  tcase_add_test(tc_core, api_calc_opt_4);
  tcase_add_test(tc_core, api_calc_opt_5);
  tcase_add_test(tc_core, api_calc_opt_6);
  tcase_add_test(tc_core, api_calc_opt_7);
  tcase_add_test(tc_core, api_calc_opt_8);
  tcase_add_test(tc_core, api_calc_opt_9);
  tcase_add_test(tc_core, api_calc_opt_10);
  tcase_add_test(tc_core, api_calc_opt_11);
  tcase_add_test(tc_core, api_calc_opt_12);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *api_calc_with_x_suit(void) {
  Suite *suite = suite_create("api_calc_with_x");
  TCase *tc_core = tcase_create("core_of_api_calc_with_x");
  tcase_add_test(tc_core, api_calc_with_x_opt_1);
  tcase_add_test(tc_core, api_calc_with_x_opt_2);
  tcase_add_test(tc_core, api_calc_with_x_opt_3);
  tcase_add_test(tc_core, api_calc_with_x_opt_4);
  tcase_add_test(tc_core, api_calc_with_x_opt_5);
  tcase_add_test(tc_core, api_calc_with_x_opt_6);
  tcase_add_test(tc_core, api_calc_with_x_opt_7);
  tcase_add_test(tc_core, api_calc_with_x_opt_8);
  tcase_add_test(tc_core, api_calc_with_x_opt_9);
  tcase_add_test(tc_core, api_calc_with_x_opt_10);
  tcase_add_test(tc_core, api_calc_with_x_opt_11);
  tcase_add_test(tc_core, api_calc_with_x_opt_12);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *api_infix_to_postfix_suit(void) {
  Suite *suite = suite_create("api_infix_to_postfix");
  TCase *tc_core = tcase_create("core_api_infix_to_postfix");
  tcase_add_test(tc_core, api_infix_to_postfix_opt_1);
  tcase_add_test(tc_core, api_infix_to_postfix_opt_2);
  tcase_add_test(tc_core, api_infix_to_postfix_opt_3);
  tcase_add_test(tc_core, api_infix_to_postfix_opt_4);
  tcase_add_test(tc_core, api_infix_to_postfix_opt_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}

/*  SUITES EXECUTION SCRIPT */

void s21_suit_execution(Suite *suite, int *failed_count, char *suite_name) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_set_log(suite_runner, suite_name);
  srunner_run_all(suite_runner, CK_NORMAL);
  *failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

/*  TESTS MAIN */

int main(void) {
  int failed_count = 0;

  s21_suit_execution(api_calc_suit(), &failed_count,
                     "tests/logs/api_calc_tests.log");
  s21_suit_execution(api_calc_with_x_suit(), &failed_count,
                     "tests/logs/api_calc_with_x_tests.log");
  s21_suit_execution(api_infix_to_postfix_suit(), &failed_count,
                     "tests/logs/api_infix_to_postfix_tests.log");

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
