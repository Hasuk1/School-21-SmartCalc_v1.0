#ifndef MODULES_H
#define MODULES_H

#define OK 0
#define ERROR 1

bool valid_str(const char* str);
void infixToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);

#endif // MODULES_H