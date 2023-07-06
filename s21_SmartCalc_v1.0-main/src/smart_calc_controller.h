/* created by sheritsh // Oleg Polovinko ※ School 21, Kzn */

#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <iso646.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255

#include "modules/headers/calculate.h"
#include "modules/headers/deposit_calc.h"
#include "modules/headers/input_validation.h"
#include "modules/headers/loan_calc.h"
#include "modules/headers/shunting_yard.h"
#include "modules/headers/stack.h"
#include "modules/headers/tokens_devider.h"

/**
 * @brief Main function and entry point. Receives a mathematical expression
 * string as input, checks it and writes the result to a variable.
 * @param str mathematical expression string
 * @param res result
 * @return BOOL :
 * 0 - SUCCESS
 * 1 - FAILURE
 */
int api_calculate_str(const char* str, long double* res);

/**
 * @brief The function converts normal infix notation to reverse polish notation
 * (or postfix). The string to be written must be at least 510 characters!
 * (MAX_INPUT_LEN * 2)
 * @param str mathematical expression string
 * @return BOOL :
 * 0 - SUCCESS
 * 1 - FAILURE
 */
int api_infix_to_postfix_notation(const char* str, char* res_str);

/**
 * @brief Modification of the main function, replaces unknown x values
 * ​​with given ones and writes the result to a variable.
 * @param str mathematical expression string
 * @param x value for unknown variable (X)
 * @param res result
 * @return BOOL :
 * 0 - SUCCESS
 * 1 - FAILURE
 */
int api_calculate_str_with_x(const char* str, long double x, long double* res);

#endif  // SMART_CALC_H
