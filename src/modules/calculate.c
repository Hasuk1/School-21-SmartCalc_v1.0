#include "modules.h"

void get_operand(char *num_buf, int *num_buf_len, NumStack *num_stack) {
  if (*num_buf_len > 0) {
    num_buf[*num_buf_len] = '\0';
    long double num = atof(num_buf);
    push_num(num_stack, num);
    *num_buf_len = 0;
  }
}

void calc_simple(long double op1, long double op2, const char *postfix, int i,
                 NumStack *num_stack, int *exit_status) {
  if (postfix[i] == '+') {
    push_num(num_stack, op1 + op2);
  } else if (postfix[i] == '-') {
    push_num(num_stack, op1 - op2);
  } else if (postfix[i] == '*') {
    push_num(num_stack, op1 * op2);
  } else if (postfix[i] == '/') {
    if (op2 != 0) {
      push_num(num_stack, op1 / op2);
    } else
      *exit_status = ERROR_INVALID_EXPRESSION;
  } else if (postfix[i] == '^') {
    push_num(num_stack, pow(op1, op2));
  } else if (postfix[i] == '%') {
    push_num(num_stack, fmod(op1, op2));
  }
}

void calc_func(long double op, char *postfix, int i, NumStack *num_stack,
               int *exit_status) {
  if (is_cos(postfix, i)) {
    push_num(num_stack, cos(op));
  } else if (is_sin(postfix, i)) {
    push_num(num_stack, sin(op));
  } else if (is_tan(postfix, i)) {
    push_num(num_stack, tan(op));
  } else if (is_acos(postfix, i)) {
    push_num(num_stack, acos(op));
  } else if (is_asin(postfix, i)) {
    push_num(num_stack, acos(op));
  } else if (is_atan(postfix, i)) {
    push_num(num_stack, acos(op));
  } else if (is_ln(postfix, i)) {
    if (op > 0) {
      push_num(num_stack, log(op));
    } else
      *exit_status = ERROR_INVALID_EXPRESSION;
  } else if (is_log(postfix, i)) {
    if (op > 0) {
      push_num(num_stack, log10(op));
    } else
      *exit_status = ERROR_INVALID_EXPRESSION;
  } else if (is_sqrt(postfix, i)) {
    if (op >= 0) {
      push_num(num_stack, sqrt(op));
    } else
      *exit_status = ERROR_INVALID_EXPRESSION;
  } else if (postfix[i] == '~') {
    push_num(num_stack, op * -1);
  } else if (postfix[i] == '&') {
    push_num(num_stack, op);
  }
}

void trim_null(char *result, NumStack *num_stack) {
  long double res = pop_num(num_stack);
  char buf[MAX_SIZE] = {0};
  sprintf(buf, "%.7Lf", res);
  int i = strlen(buf) - 1;
  if (i <= 14) {
    sprintf(result, "%s", buf);
    for (; result[i] == '0'; i--) result[i] = '\0';
    if (result[i] == '.' || result[i] == ',') result[i] = '\0';
  } else {
    sprintf(result, "%Le", res);
  }
}

void evaluate_postfix(char *postfix, long double x, char *result) {
  NumStack num_stack;
  init_num_stack(&num_stack);
  char num_buf[MAX_SIZE];
  int num_buf_len = 0, exit_status = OK;
  for (int i = 0; (postfix[i]) != '\0'; i++) {
    int fun_len = 0;
    if (is_numeric(postfix, i)) {
      if (postfix[i] == 'x') {
        push_num(&num_stack, x);
      } else
        num_buf[num_buf_len++] = postfix[i];
    } else if (postfix[i] == ' ') {
      get_operand(num_buf, &num_buf_len, &num_stack);
    } else if (is_operator(postfix[i])) {
      get_operand(num_buf, &num_buf_len, &num_stack);
      long double op2 = pop_num(&num_stack);
      long double op1 = pop_num(&num_stack);
      calc_simple(op1, op2, postfix, i, &num_stack, &exit_status);
    } else if (is_function(postfix, i, &fun_len) || postfix[i] == '~' ||
               postfix[i] == '&') {
      get_operand(num_buf, &num_buf_len, &num_stack);
      long double op = pop_num(&num_stack);
      calc_func(op, postfix, i, &num_stack, &exit_status);
      if (fun_len != 0) i += fun_len - 1;
    } else if (its_fun(postfix[i])) {
    } else
      exit_status = ERROR_INVALID_EXPRESSION;
  }
  get_operand(num_buf, &num_buf_len, &num_stack);
  if (exit_status == OK) {
    trim_null(result, &num_stack);
  } else
    sprintf(result, "%s", "ERROR");
}
