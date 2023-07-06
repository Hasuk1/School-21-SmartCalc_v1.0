#include "headers/tokens_devider.h"

char* token_divider(char* str) {
  if (str == NULL) {
    return NULL;
  }

  char* output_str = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
  if (output_str != NULL) {
    memset(output_str, '\0', MAX_LEN * 2 + 1);

    for (char* ptr = str; *ptr != '\0'; ptr++) {
      char cur_char = *ptr;
      char cur_token[MAX_LEN] = {'\0'};
      int step = 0;

      if (cur_char == '.' || strchr(NUMBERS, (int)cur_char)) {
        bool is_exp_notation = check_exp_notation(ptr);
        if (is_exp_notation) {
          // for exp_notated
          step = exp_notation_length(ptr) - 1;
          strncpy(cur_token, ptr, step + 1);
        } else {
          step = strspn(ptr, REAL_NUMBS) - 1;
          strncpy(cur_token, ptr, step + 1);
        }
      } else if (cur_char == 'e') {
      } else if (strchr(OPERATORS, (int)cur_char) ||
                 strchr(BRACKETS, (int)cur_char) || cur_char == 'x') {
        strncpy(cur_token, ptr, 1);
      } else if (strchr(FUNCS, (int)cur_char)) {
        step = handle_functions(ptr) - 1;
        strncpy(cur_token, ptr, step + 1);
      }
      ptr += step;
      strcat(output_str, cur_token);
      strcat(output_str, " ");
    }
  }

  return output_str;
}

int handle_functions(char* ptr) {
  if (ptr == NULL) {
    return 0;
  }

  int func_size = 0;
  char str_to_analyze[6] = {'\0'};
  strncat(str_to_analyze, ptr, 5);

  if (*ptr == 'a') {
    if (strstr(str_to_analyze, "asin") || strstr(str_to_analyze, "acos") ||
        strstr(str_to_analyze, "atan")) {
      func_size = 4;
    }
  } else if (*ptr == 'c') {
    if (strstr(str_to_analyze, "cos")) {
      func_size = 3;
    }
  } else if (*ptr == 'l') {
    if (strstr(str_to_analyze, "ln")) {
      func_size = 2;
    } else if (strstr(str_to_analyze, "log")) {
      func_size = 3;
    }
  } else if (*ptr == 'm') {
    if (strstr(str_to_analyze, "mod")) {
      func_size = 3;
    }
  } else if (*ptr == 's') {
    if (strstr(str_to_analyze, "sin")) {
      func_size = 3;
    } else if (strstr(str_to_analyze, "sqrt")) {
      func_size = 4;
    }
  } else if (*ptr == 't') {
    if (strstr(str_to_analyze, "tan")) {
      func_size = 3;
    }
  }

  return func_size;
}

bool check_exp_notation(char* str) {
  if (str == NULL) {
    return false;
  }

  bool is_exp_notation = false;
  bool is_number_end = false;

  for (char* ptr = str; *ptr != '\0' && !is_number_end; ptr++) {
    if (*ptr == 'e') {
      is_exp_notation = true;
    } else if (!strchr("1234567890.", (int)*ptr)) {
      is_number_end = true;
    }
  }

  return is_exp_notation;
}

int exp_notation_length(char* str) {
  if (str == NULL) {
    return 0;
  }

  bool has_sign = false;
  int real_part = (int)strspn(str, "1234567890.");

  str += real_part + 1;
  if (*str == '+' || *str == '-') {
    has_sign = true;
    str++;
  }
  int exp_part = (int)strspn(str, "1234567890");

  return real_part + has_sign + exp_part + 1;
}

void missing_mult_signs_handler(char* str) {
  if (str != NULL) {
    char prev_lexema[MAX_LEN + 1] = {'\0'};
    int current_word = 0;

    for (char* ptr = str; *ptr != '\0'; ptr++) {
      // arrange lexema
      if (current_word) {
        for (char* insptr = ptr; *insptr != ' '; insptr++) {
        }
        // handling multiplier for numbers
        if (*ptr == 'x' || *ptr == '(' || strchr(FUNCS, (int)*ptr)) {
          if (strpbrk(prev_lexema, ")x.0123456789")) {
            memmove(ptr + 2, ptr, strlen(ptr));
            *ptr = '*';
            *(ptr + 1) = ' ';
          }
        } else if (strchr(REAL_NUMBS, (int)*ptr)) {
          if (strpbrk(prev_lexema, ")x")) {
            memmove(ptr + 2, ptr, strlen(ptr));
            *ptr = '*';
            *(ptr + 1) = ' ';
          }
        }
      }
      // now create prev lexema for next operation
      for (char* insptr = ptr; *insptr != ' '; insptr++) {
        strncpy(prev_lexema, insptr, 1);
      }
      // moving to the next token
      while (*ptr != ' ') {
        ptr++;
      }
      current_word++;
    }
  }
}

void unary_operators_handler(char* str) {
  if (str != NULL) {
    if (*str == '+') {
      *str = 'p';
    } else if (*str == '-') {
      *str = '~';
    }

    char prev_lexema[MAX_LEN + 1] = {'\0'};
    int current_word = 0;

    for (char* ptr = str; *ptr != '\0'; ptr++) {
      if (current_word) {
        if (*ptr == '+' || *ptr == '-') {
          if (strchr(prev_lexema, '(')) {
            if (*ptr == '+') {
              *ptr = 'p';
            } else {
              *ptr = '~';
            }
          }
        }
      }
      for (char* insptr = ptr; *insptr != ' '; insptr++) {
        strncpy(prev_lexema, insptr, 1);
      }
      while (*ptr != ' ') {
        ptr++;
      }
      current_word++;
    }
  }
}

void add_end_of_line(char* str) {
  if (str != NULL) {
    *(str + strlen(str)) = '<';
    *(str + strlen(str) + 1) = '\0';
  }
}

void x_replacement_to_value(char* str, long double value) {
  if (str != NULL) {
    size_t str_length_before = strlen(str);
    int allowed_amount = MAX_LEN - str_length_before;
    char insert_value[256] = {'\0'};
    memset(insert_value, '\0', 256);
    insert_value[0] = '(';
    insert_value[1] = ' ';
    snprintf(insert_value + 2, MAX_LEN - 4, "%Lf", value);
    if (insert_value[2] == '-') {
      insert_value[2] = '~';
      memmove(insert_value + 4, insert_value + 3, strlen(insert_value));
      insert_value[3] = ' ';
    }
    insert_value[strlen(insert_value)] = ' ';
    insert_value[strlen(insert_value)] = ')';
    int value_length = strlen(insert_value);
    for (char* ptr = str; *ptr != '\0' && (allowed_amount - value_length) > 0;
         ptr++) {
      if (*ptr == 'x') {
        if (allowed_amount) {
          memmove(ptr + value_length - 1, ptr, strlen(ptr));
          memmove(ptr, insert_value, value_length);
          allowed_amount -= value_length;
        }
      }
    }
  }
}
