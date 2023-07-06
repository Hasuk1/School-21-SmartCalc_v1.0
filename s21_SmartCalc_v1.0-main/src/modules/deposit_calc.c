#include "headers/deposit_calc.h"

long double get_tax_amount(long double total_amount, long double tax_rate) {
  // Рассчитывает сумму налога на основе общей суммы и ставки налога.
  return total_amount * tax_rate / 100;
}

long double get_total_amount(long double deposit_amount,
                             long double earned_money, long double tax_amount) {
  // Рассчитывает общую сумму на основе суммы депозита, заработанных денег и налоговой суммы.
  return deposit_amount + earned_money - tax_amount;
}

long double get_total_earned(long double *deposit_amount, double term,
                             long double interest_rate, int MODE,
                             bool is_capitalization, long double replenishments,
                             long double withdraws) {
  long double earned_money_amount = 0;

  // Определение периода в зависимости от режима (ежемесячно или ежегодно).
  int period = MODE == MONTHLY ? 12 : 1;

  // Приведение пополнений и снятий к соответствующему периоду.
  replenishments = MODE == MONTHLY ? replenishments : replenishments * 12;
  withdraws = MODE == MONTHLY ? withdraws : withdraws * 12;

  for (int i = 0; (double)i < term; i++) {
    long double cumulative_earnings = 0;

    if (MODE == MONTHLY) {
      // Расчет накопленных доходов при ежемесячной капитализации.
      cumulative_earnings = *deposit_amount * interest_rate / 100 / period;
    }

    if (MODE == YEARLY) {
      // Расчет накопленных доходов при ежегодной капитализации.
      if (i % 11 == 0 && i != 0) {
        cumulative_earnings = *deposit_amount * interest_rate / 100 / period;
      }
    }

    // Обновление суммы депозита с учетом пополнений и снятий.
    *deposit_amount += replenishments;
    *deposit_amount -= withdraws;

    if (is_capitalization) {
      // Капитализация накопленных доходов, если установлен флаг is_capitalization.
      *deposit_amount += cumulative_earnings;
    }

    earned_money_amount += cumulative_earnings;
  }

  return earned_money_amount;
}

