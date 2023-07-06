#ifndef STACK_H
#define STACK_H

/* STACK STRUCTURES */

typedef struct stack_struct {
  int length;
  char **tokens;
} calc_stack_t;

typedef struct double_stack_struct {
  int length;
  long double *values;
} double_stack_t;

#include "../../smart_calc_controller.h"

/* CHAR* STACK FUNCTIONS */

/**
 * @brief Initializes the stack. Need free() after usage. Returns NULL in case
 * of error.
 * @return pointer to created stack || NULL
 */
calc_stack_t *init_stack();

/**
 * @brief Checks if the stack is empty
 * @param stack pointer to the stack
 * @return BOOL :
 * 0 - STACK IS NOT EMPTY
 * 1 - STACK IS EMPTY
 */
bool is_stack_empty(calc_stack_t *stack);

/**
 * @brief Checks if the stack is full
 * @param stack pointer to the stack
 * @return BOOL :
 * 0 - STACK IS NOT FULL
 * 1 - STACK IS FULL
 */
bool is_stack_full(calc_stack_t *stack);

/**
 * @brief Pushes char* onto the stack
 * @param stack pointer to the stack
 * @param token char* math token
 */
void push(calc_stack_t *stack, char *token);

/**
 * @brief Gets the top of the stack and does not remove the value from there
 * @param stack pointer to the stack
 * @return Top value on the stack
 */
char *peek(calc_stack_t *stack);

/**
 * @brief Gets the top of the stack and removes the value from there
 * @param stack pointer to the stack
 * @return Top value on the stack
 */
char *pop(calc_stack_t *stack);

/**
 * @brief Sets the stack length to zero and clears the allocated memory for the
 * values ​​inside it
 * @param stack pointer to the stack
 */
void remove_stack(calc_stack_t *stack);

/* LONG DOUBLE STACK FUNCTIONS */

/**
 * @brief Initializes the stack. Need free() after usage. Returns NULL in case
 * of error.
 * @return pointer to created stack || NULL
 */
double_stack_t *init_double_stack();

/**
 * @brief Checks if the stack is empty
 * @param stack pointer to the stack
 * @return BOOL :
 * 0 - STACK IS NOT EMPTY
 * 1 - STACK IS EMPTY
 */
bool is_double_stack_empty(double_stack_t *stack);

/**
 * @brief Checks if the stack is full
 * @param stack pointer to the stack
 * @return BOOL :
 * 0 - STACK IS NOT FULL
 * 1 - STACK IS FULL
 */
bool is_double_stack_full(double_stack_t *stack);

/**
 * @brief Pushes long double value onto the stack
 * @param stack pointer to the stack
 * @param value long double value
 */
void push_into_double(double_stack_t *stack, long double value);

/**
 * @brief Gets the top of the stack and does not remove the value from there
 * @param stack pointer to the stack
 * @return Top value on the stack
 */
long double peek_double_stack(double_stack_t *stack);

/**
 * @brief Gets the top of the stack and removes the value from there
 * @param stack pointer to the stack
 * @return Top value on the stack
 */
long double pop_double_stack(double_stack_t *stack);

/**
 * @brief Sets the stack length to zero and clears the allocated memory for the
 * values ​​inside it
 * @param stack pointer to the stack
 */
void remove_double_stack(double_stack_t *stack);

#endif  // STACK_H
