#include <check.h>

#include "../modules/modules.h"

START_TEST(calculate_1) {
  char *infix = "cos(sin(tan(0.5)))";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "0.5 tansincos ";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "0.8680519";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_2) {
  char *infix = "-8/(2+3)*(7-2)+6";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "8~ 2 3 +/ 7 2 -* 6 +";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "-2";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_3) {
  char *infix = "(10.5-2.2)*(4.8+2.3)-1.7/3";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "10.5 2.2 - 4.8 2.3 +* 1.7 3 / -";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "58.3633333";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_4) {
  char *infix =
      "((5.5^3 + 3^2) * (2.7^2 - 6^3)) / (2^4 + 10^2) * (4.2^5 - 1.2^6)";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix =
      "5.5 3^ 3 2 ^+ 2.7 2^ 6 3 ^-* 2 4^ 10 2 ^+/ 4.2 5^ 1.2 6 ^- *";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "-411439.5250193";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_5) {
  char *infix = "sqrt(16)+ln(1)*log(10)/sqrt(25)";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "16 sqrt 1 ln 10 log* 25 sqrt / +";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "4";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_6) {
  char *infix = "(sqrt(16)+sin(1)*cos(2)/"
                "tan(0.5)-asin(0.5)^acos(0.3)%2*atan(0.8)*ln(2)*log(100))/"
                "cos(sin(tan(0.5)))";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "16 sqrt 1 sin 2 cos* 0.5 tan/+ 0.5 asin 0.3 acos^ 2% "
                      "0.8 atan* 2 ln* 100 log*- 0.5 tansincos /";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "2.7801183";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_7) {
  char *infix =
      "cos(5.89-5.6568)+(+4 + sin(x) * cos(2) / tan(0.5) - asin(x)^acos(0.3) % "
      "2 * atan(x) * ln(2) * log10(100)) / cos(sin(tan(x)))";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "5.89 5.6568 -cos 4& x sin 2 cos* 0.5 tan/+ x asin 0.3 "
                      "acos^ 2% x atan* 2 ln* 10 100 log*- x tansincos / +";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0.49879, result);
  char *exp_result = "-18.4983629";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_8) {
  char *infix = "(4 + sin(x) * cos(2) / 0 - asin(x)^acos(0.3) % 2 * atan(x) * "
                "ln(2) * log10(100)) / cos(sin(tan(x)))";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "4 x sin 2 cos* 0/+ x asin 0.3 acos^ 2% x atan* 2 ln* 10 "
                      "100 log*- x tansincos /";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0.49879, result);
  char *exp_result = "ERROR";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_9) {
  char *infix = "(4 + sin(x) * cohs(2) / tan(0.5)) - asin(x)^acos(((0.3) % 2 * "
                "atan(x) * ln(2) * log10(100)) / cos(sin(tan(x)))";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "4 x sin*+(coh 2 ";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, ERROR_INVALID_EXPRESSION);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0.49879, result);
  char *exp_result = "ERROR";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_10) {
  char *infix = "((10.5-2.2)*(4.8+2.3)-1.7/3)^9";
  char postfix[MAX_SIZE] = {0};
  int exit_status = infix_to_postfix(infix, postfix);
  char *exp_postfix = "10.5 2.2 - 4.8 2.3 +* 1.7 3 /- 9 ^";
  ck_assert_str_eq(postfix, exp_postfix);
  ck_assert_int_eq(exit_status, OK);
  char result[MAX_SIZE];
  evaluate_postfix(postfix, 0, result);
  char *exp_result = "7.857073e+15";
  ck_assert_str_eq(result, exp_result);
}

START_TEST(calculate_credit_1) {
  double monthPaymentsAnn = calc_month_payments_ann(1000000, 13, 1, 23.13);
  ck_assert_double_eq_tol(87697.81, monthPaymentsAnn, 0.01);
  double termMonth = calc_term_month(13, 1);
  double totalPayment = calc_total_payment(monthPaymentsAnn, termMonth);
  ck_assert_double_eq_tol(1140071.55, totalPayment, 0.01);
  double overPay = calc_over_payment(totalPayment, 1000000);
  ck_assert_double_eq_tol(140071.55, overPay, 0.01);
}

START_TEST(calculate_credit_2) {
  double monthPaymentsAnn = calc_month_payments_ann(31314, 23, 12, 1.3245);
  ck_assert_double_eq_tol(131.68, monthPaymentsAnn, 0.01);
  double termMonth = calc_term_month(23, 12);
  double totalPayment = calc_total_payment(monthPaymentsAnn, termMonth);
  ck_assert_double_eq_tol(36342.61, totalPayment, 0.01);
  double overPay = calc_over_payment(totalPayment, 31314);
  ck_assert_double_eq_tol(5028.61, overPay, 0.01);
}

START_TEST(calculate_credit_3) {
  double first_pay = 0, last_pay = 0, total_pay_dif = 0;
  calc_month_payments_diff(1000000, 13, 1, 23.13, &first_pay, &last_pay,
                           &total_pay_dif);
  ck_assert_double_eq_tol(96198.08, first_pay, 0.01);
  ck_assert_double_eq_tol(78405.77, last_pay, 0.01);
  ck_assert_double_eq_tol(1134925.00, total_pay_dif, 0.01);
  double overPay = calc_over_payment(total_pay_dif, 1000000);
  ck_assert_double_eq_tol(134925.00, overPay, 0.01);
}
START_TEST(calculate_credit_4) {
  double first_pay = 0, last_pay = 0, total_pay_dif = 0;
  calc_month_payments_diff(31314, 23, 12, 1.3245, &first_pay, &last_pay,
                           &total_pay_dif);
  ck_assert_double_eq_tol(148.02, first_pay, 0.01);
  ck_assert_double_eq_tol(113.58, last_pay, 0.01);
  ck_assert_double_eq_tol(36100.95, total_pay_dif, 0.01);
  double overPay = calc_over_payment(total_pay_dif, 31314);
  ck_assert_double_eq_tol(4786.95, overPay, 0.01);
}

START_TEST(calculate_deposit_1) {
  double totalInterest = calc_total(16595, 31, 12, 32.78, 1, true, 1324, 99);
  double totalTax = calc_tax_amount(totalInterest, 4.58);
  double endBalance =
      calc_total_deposit(totalInterest, 16595, totalTax, 31, 12, 1324, 99);
  ck_assert_double_eq_tol(1387706118.21, totalInterest, 0.01);
  ck_assert_double_eq_tol(63556940.21, totalTax, 0.01);
  ck_assert_double_eq_tol(1324621473.0, endBalance, 0.01);
}

START_TEST(calculate_deposit_2) {
  double totalInterest =
      calc_total(3123.24, 63, 1, 14.59, 12, false, 228.01, 228);
  double totalTax = calc_tax_amount(totalInterest, 1.26);
  double endBalance =
      calc_total_deposit(totalInterest, 3123.24, totalTax, 63, 1, 228.01, 228);
  ck_assert_double_eq_tol(2278.66, totalInterest, 0.01);
  ck_assert_double_eq_tol(28.71, totalTax, 0.01);
  ck_assert_double_eq_tol(5373.82, endBalance, 0.01);
}

Suite *

smart_calc(void) {
  Suite *s = suite_create("SmartCalcV1.0");
  TCase *smart_calc = tcase_create("smart_calc");
  TCase *credit_calc = tcase_create("credit_calc");
  TCase *deposit_calc = tcase_create("deposit_calc");

  /*SMART_CALC*/

  tcase_add_test(smart_calc, calculate_1);
  tcase_add_test(smart_calc, calculate_2);
  tcase_add_test(smart_calc, calculate_3);
  tcase_add_test(smart_calc, calculate_4);
  tcase_add_test(smart_calc, calculate_5);
  tcase_add_test(smart_calc, calculate_6);
  tcase_add_test(smart_calc, calculate_7);
  tcase_add_test(smart_calc, calculate_8);
  tcase_add_test(smart_calc, calculate_9);
  tcase_add_test(smart_calc, calculate_10);

  tcase_add_test(credit_calc, calculate_credit_1);
  tcase_add_test(credit_calc, calculate_credit_2);
  tcase_add_test(credit_calc, calculate_credit_3);
  tcase_add_test(credit_calc, calculate_credit_4);

  tcase_add_test(deposit_calc, calculate_deposit_1);
  tcase_add_test(deposit_calc, calculate_deposit_2);

  suite_add_tcase(s, smart_calc);
  suite_add_tcase(s, credit_calc);
  suite_add_tcase(s, deposit_calc);

  return s;
}

int main(void) {
  int count_failed;
  Suite *s = smart_calc();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}
