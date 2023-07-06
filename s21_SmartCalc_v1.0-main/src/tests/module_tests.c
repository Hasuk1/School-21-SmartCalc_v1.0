/* created by sheritsh // Oleg Polovinko ※ School 21, Kzn */

#include "module_tests.h"

/* TEST OPTIONS */

START_TEST(input_validation_opt_1) {
  char* sample = "2+2*2";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_2) {
  char* sample = "2^2^3";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_3) {
  char* sample = "cos(4)*sin(3)";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_4) {
  char* sample = "3.1415-21/42+12tan(5)";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_5) {
  char* sample = "19e+6-659.129+x(tan(cos(x)))";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(input_validation_opt_6) {
  char* sample = "kakayatonesurazica";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_7) {
  char* sample = "3..15";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_8) {
  char* sample = "1e--16";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_9) {
  char* sample = "29ep+cos(4)";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(input_validation_opt_10) {
  char* sample = "atan(5)+ln(3)+mod(4)+sqrb()";
  int res = is_input_valid(sample);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(tokens_devider_opt_1) {
  char* input_data = "+x-(-21)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "+ x - ( - 21 ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_2) {
  char* input_data = "3.14+56((x)22)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "3.14 + 56 ( ( x ) 22 ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_3) {
  char* input_data = "xxxxxxxxx(x)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "x x x x x x x x x ( x ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_4) {
  char* input_data = "1e-12+cos(4)/sin(2)+ln(5)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "1e-12 + cos ( 4 ) / sin ( 2 ) + ln ( 5 ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_5) {
  char* input_data = "log(log(log(sin(3))))";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "log ( log ( log ( sin ( 3 ) ) ) ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_6) {
  char* input_data = "+3247862-(-1)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "+ 3247862 - ( - 1 ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_7) {
  char* input_data = "12/03/1997";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "12 / 03 / 1997 ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_8) {
  char* input_data = "0log(x)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, "0 log ( x ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_9) {
  char* input_data = ".123123123+12398172387126387123613412";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(token_str, ".123123123 + 12398172387126387123613412 ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(tokens_devider_opt_10) {
  char* input_data = "^3^2^10*(24124-1e16)cos(5)/0log(x)";
  char* token_str = token_divider(input_data);
  int is_allocated = false;
  if (token_str != NULL) {
    is_allocated = true;
    ck_assert_str_eq(
        token_str, "^ 3 ^ 2 ^ 10 * ( 24124 - 1e16 ) cos ( 5 ) / 0 log ( x ) ");
    free(token_str);
    token_str = NULL;
  }
  ck_assert_int_eq(is_allocated, SUCCESS);
}
END_TEST

START_TEST(stack_opt_1) {
  // char *stack
  int is_error = false;
  calc_stack_t* teststack = init_stack();
  if (teststack != NULL) {
    push(teststack, "I");
    push(teststack, "am");
    push(teststack, "egoist");
    ck_assert_int_eq(teststack->length, 3);
    char* top = peek(teststack);
    ck_assert_str_eq(top, "egoist");
    top = pop(teststack);
    ck_assert_str_eq(top, "egoist");
    top = pop(teststack);
    ck_assert_str_eq(top, "am");
    remove_stack(teststack);
    if (teststack->tokens != NULL) {
      is_error = 1;
    }
    free(teststack);
    teststack = NULL;
  } else {
    is_error = 1;
  }
  ck_assert_int_eq(is_error, false);
}
END_TEST

START_TEST(stack_opt_2) {
  // long double* stack
  int is_error = false;
  double_stack_t* teststack = init_double_stack();
  if (teststack != NULL) {
    push_into_double(teststack, 5);
    push_into_double(teststack, 10);
    push_into_double(teststack, 97);
    ck_assert_int_eq(teststack->length, 3);
    long double top = peek_double_stack(teststack);
    ck_assert_ldouble_eq(top, 97);
    top = pop_double_stack(teststack);
    ck_assert_ldouble_eq(top, 97);
    top = pop_double_stack(teststack);
    ck_assert_ldouble_eq(top, 10);
    remove_double_stack(teststack);
    if (teststack->values != NULL) {
      is_error = 1;
    }
    free(teststack);
    teststack = NULL;
  } else {
    is_error = 1;
  }
  ck_assert_int_eq(is_error, false);
}
END_TEST

START_TEST(shunting_yard_opt_1) {
  char input[510] = {'\0'};
  strcpy(input, "25 + 25 <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "25 25 + ");
}
END_TEST

START_TEST(shunting_yard_opt_2) {
  char input[510] = {'\0'};
  strcpy(input, "x ^ 2 ^ 3 * ( 2 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "x 2 3 ^ ^ 2 * ");
}
END_TEST

START_TEST(shunting_yard_opt_3) {
  char input[510] = {'\0'};
  strcpy(input, "cos ( 4 ) + sin ( 15 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "4 15 sin + cos ");
}
END_TEST

START_TEST(shunting_yard_opt_4) {
  char input[510] = {'\0'};
  strcpy(input, "2 ^ 2 - 16 + 4 * 55 / 7 <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "2 2 ^ 16 - 4 55 * 7 / + ");
}
END_TEST

START_TEST(shunting_yard_opt_5) {
  char input[510] = {'\0'};
  strcpy(input, "3.14 + mod ( x ) + ( ~ 2 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "3.14 x 2 ~ + mod + ");
}
END_TEST

START_TEST(shunting_yard_opt_6) {
  char input[510] = {'\0'};
  strcpy(input, "p 7 - tan ( 6 ) + 1e4 <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "7 6 1e4 + tan - p ");
}
END_TEST

START_TEST(shunting_yard_opt_7) {
  char input[510] = {'\0'};
  strcpy(input, "acos ( 6 ) + asin ( 9 ) / atan ( 0.5 ) + sqrt ( 1e-1 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "6 9 0.5 1e-1 sqrt + atan / asin + acos ");
}
END_TEST

START_TEST(shunting_yard_opt_8) {
  char input[510] = {'\0'};
  strcpy(input, "ln ( x ) + x * x * log ( 3e-6 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "x x x * 3e-6 log * + ln ");
}
END_TEST

START_TEST(shunting_yard_opt_9) {
  char input[510] = {'\0'};
  strcpy(input, "0 * log ( 12 ) * x * x * x * log ( 1997 ) <");
  dijkstra_runner(input);
  ck_assert_str_eq(input, "0 12 x * x * x * 1997 log * log * ");
}
END_TEST

START_TEST(shunting_yard_opt_10) {
  char input[510] = {'\0'};
  strcpy(input,
         "7777 + 77777 - 66666666999999999 ^ 4 ^ 2 - 896 / 3.1412412412412 <");
  dijkstra_runner(input);
  ck_assert_str_eq(
      input,
      "7777 77777 + 66666666999999999 4 2 ^ ^ - 896 3.1412412412412 / - ");
}
END_TEST

START_TEST(calculate_opt_1) {
  char* input = "21 42 + ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 63.000000);
}
END_TEST

START_TEST(calculate_opt_2) {
  char* input = "2 2 + 1 ~ - mod ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 5.000000);
}
END_TEST

START_TEST(calculate_opt_3) {
  char* input = "3 1 - 5 1 1 ^ tan * sin / cos ";
  long double res = calculate_res(input);
  int test_res = fabsl(res - (-0.420225)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(calculate_opt_4) {
  char* input = "15 30 2 9 sqrt * atan / asin + acos ";
  long double res = calculate_res(input);
  int test_res = fabsl(res - (-0.308071)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(calculate_opt_5) {
  char* input = "2 2 3 ^ ^ ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 256.000000);
}
END_TEST

START_TEST(calculate_opt_6) {
  char* input = "10 2 log ~ - ln ";
  long double res = calculate_res(input);
  int test_res = fabsl(res - (2.332244)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(calculate_opt_7) {
  char* input = "1e5 1e+4 1e-1 / + ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 200000.000000);
}
END_TEST

START_TEST(calculate_opt_8) {
  char* input =
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 1 1 + - / 3 * + 2 1 1 + + - * - ";
  long double res = calculate_res(input);
  int test_res = fabsl(res - (-30.072165)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(calculate_opt_9) {
  char* input = "2 2 2 * + ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 6.000000);
}
END_TEST

START_TEST(calculate_opt_10) {
  char* input = "5 10 + 97 + 0 12 log * + ";
  long double res = calculate_res(input);
  ck_assert_ldouble_eq(res, 112.000000);
}
END_TEST

START_TEST(loan_calc_opt_1) {
  long double res = get_monthly_payment_annuity(100000, 5, 12);
  int test_res = fabsl(res - (8560.748179)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(loan_calc_opt_2) {
  long double res = get_total_payment_annuity(8560.748, 12);
  int test_res = fabsl(res - (102728.976000)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(loan_calc_opt_3) {
  long double res = get_monthly_payment_diff(100000, 12);
  int test_res = fabsl(res - (8333.333333)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(loan_calc_opt_4) {
  long double res = get_total_payment_diff(100000, 12, 5);
  int test_res = fabsl(res - (102708.333333)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(loan_calc_opt_5) {
  long double res = get_overpayment_on_credit(100000, 102729);
  ck_assert_ldouble_eq(res, 2729);
}
END_TEST

START_TEST(loan_calc_opt_6) {
  double res = convert_years_to_months(1);
  ck_assert_double_eq(res, 12);
}
END_TEST

START_TEST(deposit_calc_opt_1) {
  long double deposit_amount = 100000;
  long double res = get_total_earned(&deposit_amount, 12, 5, 0, false, 0, 0);
  ck_assert_ldouble_eq(res, 5000);
}
END_TEST

START_TEST(deposit_calc_opt_2) {
  long double res = get_tax_amount(104850, 3);
  int test_res = fabsl(res - (3145.500000)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(deposit_calc_opt_3) {
  long double res = get_total_amount(100000, 5000, 3);
  int test_res = fabsl(res - (104997.000000)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

/*  TEST SUITES */

Suite* input_validation_suite(void) {
  Suite* suite = suite_create("input_validation_tests");
  TCase* tc_core = tcase_create("core_of_input_validation");
  tcase_add_test(tc_core, input_validation_opt_1);
  tcase_add_test(tc_core, input_validation_opt_2);
  tcase_add_test(tc_core, input_validation_opt_3);
  tcase_add_test(tc_core, input_validation_opt_4);
  tcase_add_test(tc_core, input_validation_opt_5);
  tcase_add_test(tc_core, input_validation_opt_6);
  tcase_add_test(tc_core, input_validation_opt_7);
  tcase_add_test(tc_core, input_validation_opt_8);
  tcase_add_test(tc_core, input_validation_opt_9);
  tcase_add_test(tc_core, input_validation_opt_10);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* tokens_devider_suite(void) {
  Suite* suite = suite_create("tokens_devider_tests");
  TCase* tc_core = tcase_create("core_of_tokens_devider");
  tcase_add_test(tc_core, tokens_devider_opt_1);
  tcase_add_test(tc_core, tokens_devider_opt_2);
  tcase_add_test(tc_core, tokens_devider_opt_3);
  tcase_add_test(tc_core, tokens_devider_opt_4);
  tcase_add_test(tc_core, tokens_devider_opt_5);
  tcase_add_test(tc_core, tokens_devider_opt_6);
  tcase_add_test(tc_core, tokens_devider_opt_7);
  tcase_add_test(tc_core, tokens_devider_opt_8);
  tcase_add_test(tc_core, tokens_devider_opt_9);
  tcase_add_test(tc_core, tokens_devider_opt_10);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* stack_suite(void) {
  Suite* suite = suite_create("stack_tests");
  TCase* tc_core = tcase_create("core_of_stack");
  tcase_add_test(tc_core, stack_opt_1);
  tcase_add_test(tc_core, stack_opt_2);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* shunting_yard_suite(void) {
  Suite* suite = suite_create("shunting_yard_tests");
  TCase* tc_core = tcase_create("core_of_shunting_yard");
  tcase_add_test(tc_core, shunting_yard_opt_1);
  tcase_add_test(tc_core, shunting_yard_opt_2);
  tcase_add_test(tc_core, shunting_yard_opt_3);
  tcase_add_test(tc_core, shunting_yard_opt_4);
  tcase_add_test(tc_core, shunting_yard_opt_5);
  tcase_add_test(tc_core, shunting_yard_opt_6);
  tcase_add_test(tc_core, shunting_yard_opt_7);
  tcase_add_test(tc_core, shunting_yard_opt_8);
  tcase_add_test(tc_core, shunting_yard_opt_9);
  tcase_add_test(tc_core, shunting_yard_opt_10);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* calculate_suite(void) {
  Suite* suite = suite_create("calculate_tests");
  TCase* tc_core = tcase_create("core_of_calculate");
  tcase_add_test(tc_core, calculate_opt_1);
  tcase_add_test(tc_core, calculate_opt_2);
  tcase_add_test(tc_core, calculate_opt_3);
  tcase_add_test(tc_core, calculate_opt_4);
  tcase_add_test(tc_core, calculate_opt_5);
  tcase_add_test(tc_core, calculate_opt_6);
  tcase_add_test(tc_core, calculate_opt_7);
  tcase_add_test(tc_core, calculate_opt_8);
  tcase_add_test(tc_core, calculate_opt_9);
  tcase_add_test(tc_core, calculate_opt_10);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* loan_calc_suite(void) {
  Suite* suite = suite_create("loan_calc_tests");
  TCase* tc_core = tcase_create("core_of_loan_calc");
  tcase_add_test(tc_core, loan_calc_opt_1);
  tcase_add_test(tc_core, loan_calc_opt_2);
  tcase_add_test(tc_core, loan_calc_opt_3);
  tcase_add_test(tc_core, loan_calc_opt_4);
  tcase_add_test(tc_core, loan_calc_opt_5);
  tcase_add_test(tc_core, loan_calc_opt_6);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite* deposit_calc_suite(void) {
  Suite* suite = suite_create("deposit_calc_tests");
  TCase* tc_core = tcase_create("core_of_deposit_calc");
  tcase_add_test(tc_core, deposit_calc_opt_1);
  tcase_add_test(tc_core, deposit_calc_opt_2);
  tcase_add_test(tc_core, deposit_calc_opt_3);
  suite_add_tcase(suite, tc_core);

  return suite;
}

/*  SUITES EXECUTION SCRIPT */

void s21_suit_execution(Suite* suite, int* failed_count, char* suite_name) {
  SRunner* suite_runner = srunner_create(suite);
  srunner_set_log(suite_runner, suite_name);
  srunner_run_all(suite_runner, CK_NORMAL);
  *failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

/*  TESTS MAIN */

int main(void) {
  int failed_count = 0;

  s21_suit_execution(input_validation_suite(), &failed_count,
                     "tests/logs/input_validation_tests.log");
  s21_suit_execution(tokens_devider_suite(), &failed_count,
                     "tests/logs/tokens_devider_tests.log");
  s21_suit_execution(stack_suite(), &failed_count,
                     "tests/logs/stack_tests.log");
  s21_suit_execution(shunting_yard_suite(), &failed_count,
                     "tests/logs/shunting_yard_tests.log");
  s21_suit_execution(calculate_suite(), &failed_count,
                     "tests/logs/calculate_tests.log");
  s21_suit_execution(loan_calc_suite(), &failed_count,
                     "tests/logs/loan_calc_tests.log");
  s21_suit_execution(deposit_calc_suite(), &failed_count,
                     "tests/logs/deposit_calc_tests.log");
  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
