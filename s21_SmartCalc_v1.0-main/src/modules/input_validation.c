#include "headers/input_validation.h"

bool is_input_valid(char* str) {
  // Проверяет, является ли входная строка допустимой.

  if (str == NULL) {
    return false;
  } else if (*str == 'e' || *str == ')') {
    return false;
  }

  bool is_valid = true;

  for (char* ptr = str; *ptr != '\0' && is_valid; ptr++) {
    char cur_char = *ptr;

    if (strchr(PERMITTED_SYMBOLS, (int)cur_char) != NULL) {
      // Если текущий символ является разрешенным символом.

      if (strchr(NUMBERS, (int)cur_char) || cur_char == 'x') {
        // Если текущий символ является цифрой или 'x', то это допустимо.
        // Пропускаем и переходим к следующему символу.
      } else {
        // Если текущий символ не является цифрой или 'x',
        // вызываем функцию handle_symbols для обработки специальных символов.

        int step = handle_symbols(ptr);

        if (step) {
          // Если функция handle_symbols вернула ненулевое значение,
          // значит обработка символа прошла успешно.
          // Увеличиваем указатель на соответствующий шаг.
          ptr += step - 1;
        } else {
          // Если функция handle_symbols вернула 0, обработка символа не удалась.
          is_valid = false;
        }
      }
    } else {
      // Если текущий символ не является разрешенным символом.
      is_valid = false;
    }
  }

  return is_valid;
}


int handle_symbols(char* ptr) {
  // Обрабатывает специальные символы в выражении.

  if (ptr == NULL) {
    return 0;
  }

  int valid_symbols = 0;
  char str_to_analyze[6] = {'\0'};
  strncat(str_to_analyze, ptr, 5);

  if (*ptr == '(') {
    // Если текущий символ является открывающей скобкой '(',
    // считается допустимым.
    valid_symbols = 1;

  } else if (*ptr == ')') {
    // Если текущий символ является закрывающей скобкой ')',
    // проверяется, что предыдущий символ был открывающей скобкой '(',
    // чтобы обеспечить правильное согласование скобок.
    if (*(ptr - 1) != '(') {
      valid_symbols = 1;
    }

  } else if (*ptr == '.') {
    // Если текущий символ является точкой '.',
    // вызывается функция check_is_dot_valid для проверки правильности использования точки.
    valid_symbols = (int)check_is_dot_valid(ptr);

  } else if (*ptr == 'e') {
    // Если текущий символ является символом экспоненты 'e',
    // вызывается функция handle_exponent для обработки экспоненты.
    valid_symbols = handle_exponent(ptr);

  } else if (strchr("+-*/^", (int)*ptr)) {
    // Если текущий символ является одним из операторов '+', '-', '*', '/', '^',
    // проверяется, что следующий символ является допустимым операндом
    // и не является концом строки ('\0').
    if (strchr(OPERANDS, (int)*(ptr + 1)) && *(ptr + 1) != '\0') {
      valid_symbols = 1;
    }

  } else if (*ptr == 'a') {
    // Если текущий символ является символом 'a',
    // проверяется подстрока для определения функции арксинуса, арккосинуса или арктангенса.
    if (strstr(str_to_analyze, "asin(") || strstr(str_to_analyze, "acos(") ||
        strstr(str_to_analyze, "atan(")) {
      valid_symbols = 5;
    }

  } else if (*ptr == 'c') {
    // Если текущий символ является символом 'c',
    // проверяется подстрока для определения функции косинуса.
    if (strstr(str_to_analyze, "cos(")) {
      valid_symbols = 4;
    }

  } else if (*ptr == 'l') {
    // Если текущий символ является символом 'l',
    // проверяется подстрока для определения функции натурального логарифма (ln)
    // или логарифма по заданному основанию (log).
    if (strstr(str_to_analyze, "ln(")) {
      valid_symbols = 3;
    } else if (strstr(str_to_analyze, "log(")) {
      valid_symbols = 4;
    }

  } else if (*ptr == 'm') {
    // Если текущий символ является символом 'm',
    // проверяется подстрока для определения функции получения остатка от деления (mod).
    if (strstr(str_to_analyze, "mod(")) {
      valid_symbols = 4;
    }

  } else if (*ptr == 's') {
    // Если текущий символ является символом 's',
    // проверяется подстрока для определения функции синуса или квадратного корня.
    if (strstr(str_to_analyze, "sin(")) {
      valid_symbols = 4;
    } else if (strstr(str_to_analyze, "sqrt(")) {
      valid_symbols = 5;
    }

  } else if (*ptr == 't') {
    // Если текущий символ является символом 't',
// проверяется подстрока для определения функции тангенса.
if (strstr(str_to_analyze, "tan(")) {
valid_symbols = 4;
}
}

return valid_symbols;
}

bool check_is_dot_valid(char* str) {
  // Проверяет, является ли точка '.', расположенная в строке 'str',
  // допустимой частью числа.

  if (str == NULL) {
    return false;
  }

  bool has_significant = strchr(NUMBERS, (int)*(str - 2)) ? true : false;
  // Флаг, указывающий, есть ли значимая цифра перед точкой.
  bool is_dot_single = true;
  // Флаг, указывающий, что точка является отдельным символом.
  bool is_only_numbers = true;
  // Флаг, указывающий, что после точки идут только цифры.

  // Переходим к следующему символу и проверяем после точки.
  str++;
  if (!has_significant && (!strchr(NUMBERS, (int)*(str)) || *(str) == '\0')) {
    // Если нет значимой цифры перед точкой и следующий символ не является цифрой,
    // или символ является концом строки ('\0'), то точка не является отдельным символом.
    is_dot_single = false;
  }

  for (char* ptr = str; *ptr != '\0' && is_dot_single && is_only_numbers;
       ptr++) {
    char cur_char = *ptr;
    if (!strchr(NUMBERS, (int)cur_char)) {
      // Если текущий символ не является цифрой,
      // значит после точки идет что-то другое, кроме цифр.
      is_only_numbers = false;
      if (cur_char == '.') {
        // Если текущий символ также является точкой,
        // то точка не является отдельным символом.
        is_dot_single = false;
      }
    }
  }

  return is_dot_single;
}


int handle_exponent(char* str) {
  // Обрабатывает экспоненту в выражении, начинающуюся с указателя 'str'.
  // Возвращает количество допустимых символов в экспоненте.

  if (str == NULL) {
    return 0;
  } else if (*(str + 1) == '\0') {
    return 0;
  }

  int valid_symbols = 0;
  // Количество допустимых символов в экспоненте.
  bool error = false;
  // Флаг ошибки.

  if (strchr(NUMBERS, (int)*(str - 1))) {
    // Если предыдущий символ является цифрой.

    if (strchr("+-", (int)*(str + 1))) {
      // Если следующий символ является '+' или '-'.

      if (strchr(NUMBERS, (int)*(str + 2))) {
        // Если символ после '+' или '-' также является цифрой.

        valid_symbols += 2;
        // Увеличиваем количество допустимых символов на 2 (для '+' или '-' и цифры).
        str += 2;
        // Смещаем указатель на 2 позиции вперед.
      } else {
        error = true;
        // Если символ после '+' или '-' не является цифрой, устанавливаем флаг ошибки.
      }
    } else if (!strchr(NUMBERS, (int)*(str + 1))) {
      // Если символ после цифры не является цифрой.
      error = true;
      // Устанавливаем флаг ошибки.
    } else {
      valid_symbols++;
      // Увеличиваем количество допустимых символов на 1 (для цифры).
      str++;
      // Смещаем указатель на 1 позицию вперед.
    }

    if (!error) {
      bool is_numb_end = false;
      // Флаг, указывающий, что число закончилось.

      for (char* ptr = str; *ptr != '\0' && !is_numb_end && !error; ptr++) {
        // Проходим через каждый символ после экспоненты.

        if (strchr(NUMBERS, (int)*ptr)) {
          // Если текущий символ является цифрой.
          valid_symbols++;
          // Увеличиваем количество допустимых символов на 1 (для цифры).
        } else if (*ptr == 'e' || *ptr == '.') {
          // Если текущий символ является 'e' или '.'.
          error = true;
          // Устанавливаем флаг ошибки.
        } else {
          is_numb_end = true;
          // Устанавливаем флаг, указывающий, что число закончилось.
        }
      }
    }
  }

  return error == 0 ? valid_symbols : 0;
  // Возвращаем количество допустимых символов, если нет ошибки,
  // иначе возвращаем 0.
}

