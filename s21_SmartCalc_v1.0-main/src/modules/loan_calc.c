#include "headers/loan_calc.h"

/* ANNUITY FORMULAS */

long double get_monthly_payment_annuity(long double loan_amount,
                                        long double interest_rate,
                                        double term) {
  // Рассчитывает ежемесячный платеж по аннуитетной формуле.

  long double monthly_interest = interest_rate / 12 / 100;
  // Месячная процентная ставка.
  long double annuity_coefficient = monthly_interest *
                                    powl(1 + monthly_interest, term) /
                                    (powl(1 + monthly_interest, term) - 1);
  // Коэффициент аннуитета.
  long double annuity = annuity_coefficient * loan_amount;
  // Ежемесячный платеж (аннуитет).

  return annuity;
}

long double get_total_payment_annuity(long double annuity, double term) {
  // Рассчитывает общую сумму платежей по аннуитетной формуле.

  return annuity * term;
}

/* DIFFERENTIATED FORMULAS */

long double get_monthly_payment_diff(long double total_payment, double term) {
  // Рассчитывает ежемесячный платеж по дифференцированной формуле.
  // Средний платеж на протяжении всего срока кредита.

  return total_payment / term;
}

long double get_total_payment_diff(long double loan_amount, double term,
                                   long double interest_rate) {
  // Рассчитывает общую сумму платежей по дифференцированной формуле.

  long double non_diff_monthly_payment = loan_amount / term;
  // Недифференцированный (фиксированный) ежемесячный платеж.
  long double total_payment = 0;

  for (int month = 0; month < term; month++) {
    long double left_to_pay = loan_amount - (non_diff_monthly_payment * month);
    // Остаток задолженности за вычетом рассчитанной суммы погашения.
    long double interest_payment = left_to_pay * (interest_rate / 100 / 12);
    // Сумма процентного платежа за текущий месяц.
    long double monthly_payment = non_diff_monthly_payment + interest_payment;
    // Ежемесячный платеж (дифференцированный).
    total_payment += monthly_payment;
    // Общая сумма платежей увеличивается на текущий платеж.
  }

  return total_payment;
}

/* OVERPAYMENT ON CREDIT */
long double get_overpayment_on_credit(long double loan_amount,
                                      long double total_payment) {
  // Рассчитывает переплату по кредиту (разницу между общей суммой платежей и суммой кредита).

  return total_payment - loan_amount;
}

/* YEARS -> MONTHS CONVERTER */
double convert_years_to_months(double years) {
  // Конвертирует годы в месяцы.

  return years * 12;
}
