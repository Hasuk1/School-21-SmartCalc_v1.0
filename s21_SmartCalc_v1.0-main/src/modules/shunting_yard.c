#include "headers/shunting_yard.h"

bool dijkstra_runner(char* str) {
  if (str == NULL) {
    return false;
  }

  bool is_success = true;
  char buffer[MAX_LEN * 2 + 1] = {'\0'};
  calc_stack_t* workstack = init_stack();
  if (workstack != NULL) {
    char* token = strtok(str, " ");
    int allowed_len = MAX_LEN * 2;
    while (token != NULL && is_success &&
           allowed_len - (int)strlen(token) > 0) {
      is_success = dijkstra_logic(token, workstack, buffer);
      token = strtok(NULL, " ");
      if (token != NULL) {
        allowed_len -= (int)strlen(token) + 1;  // 1 -> size of space char
      }
    }
    remove_stack(workstack);
    free(workstack);
    workstack = NULL;
    strncpy(str, buffer, MAX_LEN * 2);
  } else {
    is_success = false;
  }

  return is_success;
}

bool dijkstra_logic(char* token, calc_stack_t* calc_stack, char* buffer) {
  if (token == NULL || calc_stack == NULL || buffer == NULL) {
    return false;
  }

  bool is_success = true;
  if (strchr("0123456789.x", (int)*token)) {
    strcat(buffer, token);
    strcat(buffer, " ");
  } else if (strchr(OPERATORS, (int)*token)) {
    if (peek(calc_stack) != NULL) {
      decide_on_operators(token, calc_stack, buffer);
    } else {
      push(calc_stack, token);
    }
  } else if (strchr(FUNCS, (int)*token) || strchr("~p", (int)*token)) {
    push(calc_stack, token);
  } else if (*token == '(') {
    push(calc_stack, token);
  } else if (*token == ')') {
    decide_on_closure_brackets(calc_stack, buffer, &is_success);
  } else if (*token == '<') {
    is_success = handle_EOL(calc_stack, buffer);
  }

  return is_success;
}

int check_precedence(int operator_code) {
  int operator_precedence = 0;

  if (operator_code == '(') {
    operator_precedence = OPEN_BRACKET;
  } else if (operator_code == '+') {
    operator_precedence = PLUS;
  } else if (operator_code == '-') {
    operator_precedence = MINUS;
  } else if (operator_code == '*') {
    operator_precedence = MULT;
  } else if (operator_code == '/') {
    operator_precedence = DIV;
  } else if (operator_code == '^') {
    operator_precedence = POW;
  }

  return operator_precedence;
}

int get_operator_int(char* token) {
  if (token == NULL) {
    return 0;
  }

  return (int)*token;
}

bool handle_EOL(calc_stack_t* calc_stack, char* buffer) {
  if (calc_stack == NULL || buffer == NULL) {
    return false;
  }

  bool res = true;
  bool has_unclosed_brackets = false;
  while (peek(calc_stack) != NULL && !has_unclosed_brackets) {
    if (*(peek(calc_stack)) == '(') {
      has_unclosed_brackets = true;
    } else {
      strcat(buffer, pop(calc_stack));
      strcat(buffer, " ");
    }
  }
  if (has_unclosed_brackets) {
    res = false;
  }

  return res;
}

void decide_on_operators(char* token, calc_stack_t* calc_stack, char* buffer) {
  if (token != NULL && calc_stack != NULL && buffer != NULL) {
    int cur_operator = get_operator_int(token);
    int operator_from_stack = get_operator_int(peek(calc_stack));
    int current_priority = check_precedence(cur_operator);

    if (current_priority > check_precedence(operator_from_stack) ||
        (current_priority == 3 && check_precedence(operator_from_stack) == 3)) {
      push(calc_stack, token);
    } else {
      bool is_stack_empty_or_priority_less = false;
      while (!is_stack_empty_or_priority_less) {
        operator_from_stack = get_operator_int(peek(calc_stack));
        if (current_priority <= check_precedence(operator_from_stack) &&
            operator_from_stack) {
          strcat(buffer, pop(calc_stack));
          strcat(buffer, " ");
        } else {
          push(calc_stack, token);
          is_stack_empty_or_priority_less = true;
        }
      }
    }
  }
}

void decide_on_closure_brackets(calc_stack_t* calc_stack, char* buffer,
                                bool* is_success) {
  if (calc_stack != NULL && buffer != NULL && is_success != NULL) {
    bool has_open_pair = false;
    bool is_end = false;

    while (!is_end && *is_success) {
      if (peek(calc_stack) != NULL) {
        if (*(peek(calc_stack)) != '(') {
          strcat(buffer, pop(calc_stack));
          strcat(buffer, " ");
        } else {
          has_open_pair = true;
          pop(calc_stack);
          is_end = true;
        }
      } else {
        is_end = true;
      }
    }
    if (!has_open_pair) {
      *is_success = false;
    }
  }
}
