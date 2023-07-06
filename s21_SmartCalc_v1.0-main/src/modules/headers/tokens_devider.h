#ifndef TOKENS_DEVIDER_H
#define TOKENS_DEVIDER_H

#include "../../smart_calc_controller.h"

/**
 * @brief The function splits strings into space-separated tokens
 * @param str pointer to the input VALIDATED string
 * @return A pointer to the new string of valid tokens.
 * Must be cleaned after use! Can return NULL!
 */
char* token_divider(char* str);

/**
 * @brief Validates functions and returns their length in a string
 * @param ptr pointer to the math function
 * @return number of math function characters
 */
int handle_functions(char* ptr);

/**
 * @brief The function checks if the character 'e' is exponential notation
 * @param str pointer to the 'e' character
 * @return bool value:
 * 1 - EXP NOTATION
 * 0 - NO
 */
bool check_exp_notation(char* str);

/**
 * @brief The function checks the length of a number written in exponential
 * notation
 * @param str pointer to the exp-notated number
 * @return length of exponentially written number
 */
int exp_notation_length(char* str);

/**
 * @brief The function adds missing multiplication signs to the string
 * @param str pointer to the string of math tokens
 */
void missing_mult_signs_handler(char* str);

/**
 * @brief The function changes all unary operators in a string to other
 * characters. + -> p, - -> ~
 * @param str pointer to the string of math tokens
 */
void unary_operators_handler(char* str);

/**
 * @brief The function makes the last character of the string of tokens
 * sign '<' for further calculations
 * @param str pointer to the string of math tokens
 */
void add_end_of_line(char* str);

/**
 * @brief
The function iterates over the string and replaces all 'X' with the input long
double value
 * @param str pointer to the input str
 * @param value long double value for peplace 'X'
 */
void x_replacement_to_value(char* str, long double value);

#endif  // TOKENS_DEVIDER_H
