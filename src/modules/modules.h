#ifndef MODULES_H
#define MODULES_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR_STACK_FULL 1
#define ERROR_STACK_EMPTY 2
#define ERROR_INVALID_EXPRESSION 3
#define ERROR_INSUFFICIENT_OPERANDS 4
#define ERROR_INVALID_OPERANDS 5
#define ERROR_UNENFORCEABILITY 6

#define MAX_SIZE 255

/*STACK_STR*/

typedef struct {
  char data[MAX_SIZE];
  int top;
} Stack;

void init_str_stack(Stack* stack);
bool is_empty_str(Stack* stack);
bool is_full_str(Stack* stack);
void push_str(Stack* stack, char element);
void push_func(Stack* stack, char* element);
char pop_str(Stack* stack);
char peek_str(Stack* stack);

/*STACK_NUM*/

typedef struct {
  long double data[MAX_SIZE];
  int top;
} NumStack;

void init_num_stack(NumStack* stack);
bool is_empty_num(NumStack* stack);
bool is_full_num(NumStack* stack);
void push_num(NumStack* stack, long double num);
long double pop_num(NumStack* stack);

/*MINIFUNC*/

bool is_numeric(const char* str, int i);
bool is_operator(const char ch);
bool is_function(const char* str, int i, int* fun_len);
bool its_fun(const char ch);
bool is_cos(const char* postfix, int i);
bool is_sin(const char* postfix, int i);
bool is_tan(const char* postfix, int i);
bool is_acos(const char* postfix, int i);
bool is_asin(const char* postfix, int i);
bool is_atan(const char* postfix, int i);
bool is_ln(const char* postfix, int i);
bool is_log(const char* postfix, int i);
bool is_sqrt(const char* postfix, int i);
bool still_exists(char str);

/*CALCULATE*/

int infix_to_postfix(char* infix, char* postfix);
void evaluate_postfix(char* postfix, long double x, char* result);

/*CREDIT*/

int calc_term_month(int term, int term_per);
double calc_month_payments_ann(double amount, int term, int term_per,
                               double rate);
double calc_total_payment(double month_pay, int term_month);
double calc_over_payment(double total_payment, double amount);
void calc_month_payments_diff(double amount, int term, int term_per,
                              double rate, double* first_pay, double* last_pay,
                              double* total_pay_dif);

/*DEPOSIT*/

int calc_period(int term, int term_per);
double calc_rate(double rate);
double calc_total(double amount, int term, int term_per, double int_rate,
                  int frq_pay, bool capitalization, double replenishments,
                  double withdraws);
double calc_tax_amount(double total_amount, double tax_rate);
double calc_total_deposit(double total_amount, double amount, double tax_amount,
                          int term, int term_per, double replenishments,
                          double withdraws);

#endif  // MODULES_H
