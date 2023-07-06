#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../../smart_calc_controller.h"
#include "stack.h"

/* OPERAND PRIORITY */
enum operator_precedence {
  OPEN_BRACKET,
  PLUS,
  MINUS = 1,
  MULT,
  DIV = 2,
  POW,
  UNARY_MINUS,
  UNARY_PLUS = 4,
};

/**
 * @brief Splits the given string into tokens and sends them to Dijkstra's
 * algorithm
 * @param str pointer to sting with tokens
 * @return BOOL :
 * 0 - failure
 * 1 - sucessful
 */
bool dijkstra_runner(char* str);

/**
 * @brief Makes a decision regarding the token according to the shunting-yard
 * algorithm
 * @param token current token
 * @param calc_stack pointer to the stack
 * @param buffer pointer to the output buffer
 * @return BOOL :
 * 0 - failure
 * 1 - sucessful
 */
bool dijkstra_logic(char* token, calc_stack_t* calc_stack, char* buffer);

/**
 * @brief Initiates actions in the algorithm when the end of the string is
 * reached
 * @param calc_stack pointer to the stack
 * @param buffer pointer to the output buffer
 * @return BOOL :
 * 0 - failure
 * 1 - sucessful
 */
bool handle_EOL(calc_stack_t* calc_stack, char* buffer);

/**
 * @brief The function checks the precedence of operator
 * @return precedence of the operator
 */
int check_precedence(int operator_code);

/**
 * @brief Gets the first character of the token, in our case a shortened version
 * of the operator
 * @param token pointer to the current token
 * @return int representation of operator
 */
int get_operator_int(char* token);

/**
 * @brief The function processes the necessary actions with the operator,
 * depending on whether there are other operators on the stack
 * @param token current token(operator)
 * @param calc_stack pointer to the stack
 * @param buffer pointer to the output buffer
 */
void decide_on_operators(char* token, calc_stack_t* calc_stack, char* buffer);

/**
 * @brief The function handles the logic of actions when the closing bracket
 * @param calc_stack pointer to the stack
 * @param buffer pointer to the output buffer
 * @param is_success pointer to the error_flag
 */
void decide_on_closure_brackets(calc_stack_t* calc_stack, char* buffer,
                                bool* is_success);

#endif  // SHUNTING_YARD_H
