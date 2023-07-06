#ifndef CALCULATE_H
#define CALCULATE_H

#include "../../smart_calc_controller.h"
#include "stack.h"

/**
 * @brief The function passes the tokens to the calculation function. And
 * calculates the final result according to the calculation algorithm of Reverse
 * Polish Notation
 * @param str pointer to the str with tokens
 * @return long double value - final result
 */
long double calculate_res(char* str);

/**
 * @brief Calculation function for calculate_res
 * @param token pointer to the current math token
 * @param calculation_stack pointer to the calc_stack
 * @param result pointer to the resulting long double
 * @return BOOL :
 * 0 - failure
 * 1 - success
 */
bool calculations(char* token, double_stack_t* calculation_stack,
                  long double* result);

/**
 * @brief Performs basic arithmetic operations
 * @param calculation_stack pointer to the calc_stack
 * @param res pointer to the resulting long double
 * @param sign incoming operator
 * @return BOOL :
 * 0 - NUMBER is NaN
 * 1 - Number is finite
 */
bool calculate_from_stack(double_stack_t* calculation_stack, long double* res,
                          int sign);

/**
 * @brief Performs calculation of all basic trigonometric functions
 * @param calculation_stack pointer to the calc_stack
 * @param res pointer to the resulting long double
 * @param func current trigonometric function
 * @return BOOL :
 * 0 - NUMBER is NaN
 * 1 - Number is finite
 */
bool calculate_func(double_stack_t* calculation_stack, long double* res,
                    char* func);

#endif  // CALCULATE_H
