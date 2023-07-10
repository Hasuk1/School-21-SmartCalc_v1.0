#include <stdbool.h>
#include <ctype.h>

bool valid_str(const char* str) {
    int openParenCount = 0;
    int closeParenCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' &&
            str[i] != '/' && str[i] != '(' && str[i] != ')') {
            return false;
        }
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            openParenCount++;
        } else if (str[i] == ')') {
            closeParenCount++;
        }

        if (closeParenCount > openParenCount) {
            return false;
        }
    }
    if (openParenCount != closeParenCount) {
        return false;
    }
    return true;
}