#include "modules.h"

int get_priority(char *str, int i) {
  int priority = 0;
  if (str[i] == '+' || str[i] == '-') {
    priority = 1;
  } else if (str[i] == '*' || str[i] == '/') {
    priority = 2;
  } else if (is_function(str, i, NULL) || str[i] == '%') {
    priority = 3;
  } else if (str[i] == '^') {
    priority = 4;
  } else if (str[i] == '~' || str[i] == '&') {
    priority = 5;
  }
  return priority;
}

void minus_to_postfix(bool *prevDigit, char *infix, int i, Stack *stack,
                      char *postfix, int *j) {
  *prevDigit = false;
  char ch = infix[i];
  if (i == 0 || infix[i + 1] == '(' || infix[i - 1] == '(') ch = '~';
  while (!is_empty_str(stack) &&
         get_priority(infix, i) <= get_priority(stack->data, stack->top)) {
    postfix[*j] = pop_str(stack);
    *j += 1;
  }
  push_str(stack, ch);
}

void digit_to_postfix(bool *prevDigit, char *postfix, int *j, char ch) {
  if (*prevDigit) {
    postfix[*j] = ch;
    *j += 1;
  } else {
    if (*j != 0) {
      if (postfix[*j - 1] != ' ') postfix[*j] = ' ';
      *j += 1;
    }
    postfix[*j] = ch;
    *j += 1;
  }
  *prevDigit = true;
}

void open_brackets_to_postfix(Stack *stack, char ch, bool *prev_digit) {
  push_str(stack, ch);
  *prev_digit = false;
}

int close_brackets_to_postfix(bool *prevDigit, char *postfix, int *j,
                              Stack *stack) {
  int exit_status = OK;
  if (*prevDigit) {
    if (postfix[*j - 1] != ' ') postfix[*j] = ' ';
    *j += 1;
    *prevDigit = false;
  }
  while (!is_empty_str(stack) && peek_str(stack) != '(') {
    postfix[*j] = pop_str(stack);
    *j += 1;
  }
  if (!is_empty_str(stack) && peek_str(stack) == '(') {
    pop_str(stack);
    int inv_fun_len = 0;
    if (!is_empty_str(stack) &&
        is_function(stack->data, stack->top, &inv_fun_len)) {
      for (int z = 0; z < inv_fun_len; z++) {
        postfix[*j] = pop_str(stack);
        *j += 1;
      }
    }
  } else
    exit_status = ERROR_INVALID_EXPRESSION;
  return exit_status;
}

void func_to_postfix(Stack *stack, int func_len, const char *infix, int i,
                     char *postfix, int *j) {
  if (postfix == NULL && infix != NULL) {
    int f = 0;
    char func_name[10] = {0};
    for (f = 0; f < func_len; f++) func_name[f] = infix[i + f];
    func_name[f + 1] = '\0';
    push_func(stack, func_name);
  } else if (infix == NULL && postfix != NULL) {
    for (int z = 0; z < func_len; z++) {
      postfix[*j] = pop_str(stack);
      *j += 1;
    }
    if (postfix[*j - 1] != ' ') {
      postfix[*j] = ' ';
      *j += 1;
    }
  }
}

void make_end_postfix(int *j, char *postfix, Stack *stack) {
  if (*j > 0) {
    postfix[*j] = ' ';
    *j += 1;
  }
  while (!is_empty_str(stack)) {
    postfix[*j] = pop_str(stack);
    *j += 1;
    if (!is_empty_str(stack)) {
      postfix[*j] = ' ';
      *j += 1;
    }
  }
  postfix[*j] = '\0';
}

int infix_to_postfix(char *infix, char *postfix) {
  Stack stack;
  init_str_stack(&stack);
  int i = 0, j = 0, exit_status = OK, func_len = 0;
  bool prev_digit = false;
  for (; still_exists(infix[i]); i++) {
    if (infix[i] == ' ') {
      continue;
    } else if (is_numeric(infix, i)) {
      digit_to_postfix(&prev_digit, postfix, &j, infix[i]);
    } else if (infix[i] == '-') {
      minus_to_postfix(&prev_digit, infix, i, &stack, postfix, &j);
    } else if (infix[i] == '(') {
      open_brackets_to_postfix(&stack, infix[i], &prev_digit);
    } else if (infix[i] == ')') {
      if (close_brackets_to_postfix(&prev_digit, postfix, &j, &stack) != OK) {
        exit_status = ERROR_INVALID_EXPRESSION;
        break;
      }
    } else if (is_function(infix, i, &func_len)) {
      func_to_postfix(&stack, func_len, infix, i, NULL, 0);
      i += (func_len - 1);
    } else {
      prev_digit = false;
      while (!is_empty_str(&stack) &&
             get_priority(infix, i) <= get_priority(stack.data, stack.top)) {
        int inv_fun_len = 0;
        if (is_function(stack.data, stack.top, &inv_fun_len)) {
          func_to_postfix(&stack, inv_fun_len, NULL, 0, postfix, &j);
          postfix[j++] = ' ';
        } else if (stack.data[stack.top] != ' ') {
          postfix[j++] = pop_str(&stack);
        } else
          pop_str(&stack);
      }
      if (infix[i] == '+' && infix[i - 1] == '(') {
        push_str(&stack, '&');
      } else
        push_str(&stack, infix[i]);
    }
  }
  make_end_postfix(&j, postfix, &stack);
  return exit_status;
}