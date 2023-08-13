#include "modules.h"

bool is_numeric(const char* str, int i) {
  return (str[i] >= '0' && str[i] <= '9') || str[i] == '.' ||
         (str[i] == '-' &&
          (str[i - 1] == 'e' || str[i - 1] == 'E' || str[i - 1] == '(')) ||
         str[i] == 'e' || str[i] == 'E' || str[i] == 'x';
}

bool is_operator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
         ch == '%';
}

bool is_function(const char* str, int i, int* fun_len) {
  bool is_func = false;
  if (str[i] == 'c' || str[i] == 's' || str[i] == 't' || str[i] == 'a' ||
      str[i] == 'l') {
    if (str[i - 1] == 'o' || str[i - 1] == 'i' || str[i - 1] == 'a') {
      if (str[i - 2] == 's' || str[i - 2] == 'n' || str[i - 2] == 'g') {
        is_func = true;
        if (fun_len != NULL) *fun_len = 3;
      }
    } else if (str[i - 1] == 'c' || str[i - 1] == 's' || str[i - 1] == 't' ||
               str[i - 1] == 'q') {
      is_func = true;
      if (fun_len != NULL) *fun_len = 4;
    } else if (str[i - 1] == 'n') {
      is_func = true;
      if (fun_len != NULL) *fun_len = 2;
    } else if (str[i + 1] == 'o' || str[i + 1] == 'i' || str[i + 1] == 'a') {
      if (str[i + 2] == 's' || str[i + 2] == 'n' || str[i + 2] == 'g') {
        is_func = true;
        if (fun_len != NULL) *fun_len = 3;
      }
    } else if (str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 't' ||
               str[i + 1] == 'q') {
      is_func = true;
      if (fun_len != NULL) *fun_len = 4;
    } else if (str[i + 1] == 'n') {
      is_func = true;
      if (fun_len != NULL) *fun_len = 2;
    }
  }
  return is_func;
}

bool its_fun(const char ch) {
  return ch == 'c' || ch == 'o' || ch == 's' || ch == 'i' || ch == 'n' ||
         ch == 't' || ch == 'a' || ch == 'q' || ch == 'r' || ch == 'l' ||
         ch == 'g';
}

bool is_cos(const char* postfix, int i) {
  return postfix[i] == 'c' && postfix[i + 1] == 'o' && postfix[i + 2] == 's';
}
bool is_sin(const char* postfix, int i) {
  return postfix[i] == 's' && postfix[i + 1] == 'i' && postfix[i + 2] == 'n';
}
bool is_tan(const char* postfix, int i) {
  return postfix[i] == 't' && postfix[i + 1] == 'a' && postfix[i + 2] == 'n';
}
bool is_acos(const char* postfix, int i) {
  return postfix[i] == 'a' && postfix[i + 1] == 'c' && postfix[i + 2] == 'o' &&
         postfix[i + 3] == 's';
}
bool is_asin(const char* postfix, int i) {
  return postfix[i] == 'a' && postfix[i + 1] == 's' && postfix[i + 2] == 'i' &&
         postfix[i + 3] == 'n';
}
bool is_atan(const char* postfix, int i) {
  return postfix[i] == 'a' && postfix[i + 1] == 't' && postfix[i + 2] == 'a' &&
         postfix[i + 3] == 'n';
}
bool is_ln(const char* postfix, int i) {
  return postfix[i] == 'l' && postfix[i + 1] == 'n';
}
bool is_log(const char* postfix, int i) {
  return postfix[i] == 'l' && postfix[i + 1] == 'o' && postfix[i + 2] == 'g';
}
bool is_sqrt(const char* postfix, int i) {
  return postfix[i] == 's' && postfix[i + 1] == 'q' && postfix[i + 2] == 'r' &&
         postfix[i + 3] == 't';
}

bool still_exists(const char str) { return str != '\0' && str != '\n'; }
