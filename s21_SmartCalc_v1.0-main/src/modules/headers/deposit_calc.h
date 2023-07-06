#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include "../../smart_calc_controller.h"

enum mode { MONTHLY, YEARLY };

/**
 * @brief Calculates how much money was earned for a given deposit.
 * @param deposit_amount initial deposit amount
 * @param term deposit term in months
 * @param interest_rate interest rate
 * @param MODE periodicity of payments 0 - MONTHLY / 1 - YEARLY
 * @param is_capitalization capitalization of interest predicative
 * @param replenishments replenishment of money
 * @param withdraws withdrawing money
 * @return total amount of earned money
 */
long double get_total_earned(long double* deposit_amount, double term,
                             long double interest_rate, int MODE,
                             bool is_capitalization, long double replenishments,
                             long double withdraws);

/**
 * @brief Calculates how much taxes were paid for the deposit.
 * @return tax amount
 */
long double get_tax_amount(long double total_amount, long double tax_rate);

/**
 * @brief Calculates total amount of money along with earned.
 * @return total amount of money
 */
long double get_total_amount(long double deposit_amount,
                             long double earned_money, long double tax_amount);

#endif  // DEPOSIT_CALC_H
