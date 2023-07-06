#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include "../../smart_calc_controller.h"

// define commonly used data types for convenience
#define PERMITTED_SYMBOLS "1234567890()+-*/^mcstalx.e"
#define NUMBERS "1234567890"
#define REAL_NUMBS "1234567890.e"
#define OPERANDS "1234567890mcstalx.("
#define OPERATORS "+-*/^"
#define BRACKETS "()"
#define FUNCS "mcstal"

/**
 * @brief A function for moving along the input line and catching forbidden
 * characters.
 * @param str pointer to the input string
 * @return bool status :
 * 1 - VALID
 * 0 - ERROR
 */
bool is_input_valid(char* str);

/**
 * @brief The function checks if the point is a real number and if it is the
 * only one.
 * @param str pointer to the 'dot' in string
 * @return bool status :
 * 1 - VALID
 * 0 - ERROR
 */
bool check_is_dot_valid(char* str);

/**
 * @brief The function checks all valid input arguments and how much space they
 * occupy in the string
 * @param ptr pointer to the argument
 * @return length of valid characters in a string
 */
int handle_symbols(char* ptr);

/**
 * @brief The function checks the validity of exponential notation
 * @param str pointer to the 'E' part of exp-notation
 * @return length of valid characters in a string
 */
int handle_exponent(char* str);

#endif  // INPUT_VALIDATION_H
