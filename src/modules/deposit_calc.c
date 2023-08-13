#include "modules.h"

int calc_period(int term, int term_per) { return term * term_per; }

double calc_rate(double rate) { return rate * 0.01; }

double calc_total(double amount, int term, int term_per, double int_rate,
                  int frq_pay, bool capitalization, double replenishments,
                  double withdraws) {
  double interest = calc_rate(int_rate), amount_buff = amount, total_earn = 0;
  int period = calc_period(term, term_per);
  if (period >= frq_pay) {
    for (int m = 1; m <= period; m++) {
      double buff_of_earn = 0;
      if (frq_pay == 1) {
        buff_of_earn = amount_buff * interest / 12;
      } else if (frq_pay == 12 && m % 12 == 0) {
        buff_of_earn = amount_buff * interest;
      }
      amount_buff = amount_buff + replenishments - withdraws;
      if (capitalization) amount_buff += buff_of_earn;
      total_earn += buff_of_earn;
    }
  }
  return total_earn;
}

double calc_tax_amount(double total_amount, double tax_rate) {
  double tax = calc_rate(tax_rate);
  return total_amount * tax;
}

double calc_total_deposit(double total_amount, double amount, double tax_amount,
                          int term, int term_per, double replenishments,
                          double withdraws) {
  int period = calc_period(term, term_per);
  double repl_and_wtdrw = (replenishments - withdraws) * period;
  return amount + total_amount - tax_amount + repl_and_wtdrw;
}
