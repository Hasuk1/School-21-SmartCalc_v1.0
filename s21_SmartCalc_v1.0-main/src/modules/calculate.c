#include "headers/calculate.h"

long double calculate_res(char* str) {
  if (str == NULL) {
    return 0;
  }

  // Создание временного массива символов для работы со строкой
  char temp[MAX_LEN + 1] = {'\0'};
  strncpy(temp, str, MAX_LEN);
  long double result = 0;
  bool is_error = false;

  // Инициализация стека с плавающей точкой
  double_stack_t* calculation_stack = init_double_stack();
  if (calculation_stack != NULL) {
    // Разделение строки на токены и выполнение вычислений
    char* token = strtok(temp, " ");
    while (token != NULL && !is_error) {
      // Выполнение вычислений и обновление стека и результата
      is_error = !calculations(token, calculation_stack, &result);
      token = strtok(NULL, " ");
    }
    // Получение окончательного результата из стека
    result = pop_double_stack(calculation_stack);

    // Освобождение стека
    remove_double_stack(calculation_stack);
    free(calculation_stack);
    calculation_stack = NULL;
  } else {
    is_error = true;
  }

  // Возврат результата или NAN в случае ошибки
  return is_error == 0 ? result : NAN;
}

bool calculations(char* token, double_stack_t* calculation_stack,
                  long double* result) {
  if (token == NULL || calculation_stack == NULL || result == NULL) {
    return false;
  }

  bool is_success = true;

  // Проверка, является ли токен числом.
  // Если да, то помещаем его в стек вычислений.
  if (strchr("0123456789.", (int)*token)) {
    push_into_double(calculation_stack, strtold(token, &token));
  }
  // Проверка, является ли токен оператором.
  // Если да, то выполняем соответствующую операцию с использованием значений из стека.
  else if (strchr(OPERATORS, (int)*token)) {
    long double res = 0;
    is_success = calculate_from_stack(calculation_stack, &res, (int)*token);
    if (is_success) {
      push_into_double(calculation_stack, res);
    }
  }
  // Обработка унарного оператора '~'. Инвертирование значения из стека.
  else if (*token == '~') {
    push_into_double(calculation_stack,
                     0 - pop_double_stack(calculation_stack));
  }
  // Обработка функции 'p'. Добавление значения из стека к самому себе.
  else if (*token == 'p') {
    push_into_double(calculation_stack,
                     0 + pop_double_stack(calculation_stack));
  }
  // Обработка других функций. Выполнение соответствующей функции с использованием значений из стека.
  else {
    long double res = 0;
    is_success = calculate_func(calculation_stack, &res, token);
    if (is_success) {
      push_into_double(calculation_stack, res);
    }
  }

  return is_success;
}

bool calculate_from_stack(double_stack_t* calculation_stack, long double* res,
                          int sign) {
  if (calculation_stack == NULL || res == NULL) {
    return false;
  }

  // Извлечение двух значений из стека
  long double val1 = pop_double_stack(calculation_stack);
  long double val2 = pop_double_stack(calculation_stack);

  // Выполнение операции в соответствии с переданным знаком
  if (sign == '+') {
    *res = val2 + val1;
  } else if (sign == '-') {
    *res = val2 - val1;
  } else if (sign == '*') {
    *res = val2 * val1;
  } else if (sign == '/') {
    *res = val2 / val1;
  } else if (sign == '^') {
    *res = powl(val2, val1);
  }

  // Проверка на NAN (не число)
  // Возвращаем true, если результат не является NAN, иначе false.
  return isnan(*res) == 0 ? true : false;
}


bool calculate_func(double_stack_t* calculation_stack, long double* res,
                    char* func) {
  if (calculation_stack == NULL || res == NULL || func == NULL) {
    return false;
  }

  // Извлечение значения из стека
  long double value = pop_double_stack(calculation_stack);

  // Выполнение соответствующей функции в зависимости от переданной строки func
  if (strstr(func, "mod")) {
    *res = fabsl(value);
  } else if (strstr(func, "cos")) {
    *res = cosl(value);
  } else if (strstr(func, "sin")) {
    *res = sinl(value);
  } else if (strstr(func, "tan")) {
    *res = tanl(value);
  } else if (strstr(func, "acos")) {
    *res = acosl(value);
  } else if (strstr(func, "asin")) {
    *res = asinl(value);
  } else if (strstr(func, "atan")) {
    *res = atanl(value);
  } else if (strstr(func, "sqrt")) {
    *res = sqrtl(value);
  } else if (strstr(func, "ln")) {
    *res = logl(value);
  } else if (strstr(func, "log")) {
    *res = log10l(value);
  }

  // Проверка на NAN (не число)
  // Возвращаем true, если результат не является NAN, иначе false.
  return isnan(*res) == 0 ? true : false;
}

