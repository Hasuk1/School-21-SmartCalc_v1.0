#ifndef LOAN_CALC_H
#define LOAN_CALC_H

#include "../../smart_calc_controller.h"

/**
 * @brief Calculate the monthly payment for an annuity loan
 * @return monthly payment value
 */
long double get_monthly_payment_annuity(long double loan_amount,
                                        long double interest_rate, double term);

/**
 * @brief Calculates how much will be paid when repaying an annuity loan
 * @return total payment value
 */
long double get_total_payment_annuity(long double annuity, double term);

/**
 * @brief Calculate the monthly payment for an differentiated loan
 * @return monthly payment value
 */
long double get_monthly_payment_diff(long double total_payment, double term);

/**
 * @brief Calculates how much will be paid when repaying an differentiated loan
 * @return total payment value
 */
long double get_total_payment_diff(long double loan_amount, double term,
                                   long double interest_rate);

/**
 * @brief Loan repayment calculation
 * @return repayment amount
 */
long double get_overpayment_on_credit(long double loan_amount,
                                      long double total_payment);

/**
 * @brief convert years to months
 * @return months
 */
double convert_years_to_months(double years);

#endif  // LOAN_CALC_H
