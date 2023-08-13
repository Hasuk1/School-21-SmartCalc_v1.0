#include "modules.h"

double calc_month_rate(double rate) { return (rate * 0.01) / 12; }

int calc_term_month(int term, int term_per) { return term * term_per; }

double calc_month_payments_ann(double amount, int term, int term_per,
                               double rate) {
  double month_rate = calc_month_rate(rate);
  int term_month = calc_term_month(term, term_per);
  double month_pay = amount * (month_rate * (pow(1 + month_rate, term_month))) /
                     (pow(1 + month_rate, term_month) - 1);
  return month_pay;
}

double calc_total_payment(double month_pay, int term_month) {
  return month_pay * term_month;
}

double calc_over_payment(double total_payment, double amount) {
  return total_payment - amount;
}

void calc_month_payments_diff(double amount, int term, int term_per,
                              double rate, double* first_pay, double* last_pay,
                              double* total_pay_dif) {
  double month_rate = calc_month_rate(rate);
  int term_month = calc_term_month(term, term_per);
  *first_pay = 0;
  *last_pay = 0;
  *total_pay_dif = 0;
  for (int i = 1; i <= term_month; i++) {
    double diff_pay = (amount / term_month) +
                      ((amount - (i - 1) * (amount / term_month)) * month_rate);
    *total_pay_dif += diff_pay;
    if (i == 1) *first_pay = diff_pay;
    if (i == term_month) *last_pay = diff_pay;
  }
}