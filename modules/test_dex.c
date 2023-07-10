#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int element) {
    if (isFull(stack)) {
        printf("Ошибка: стек переполнен.\n");
        exit(1);
    }
    stack->data[++stack->top] = element;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Ошибка: стек пуст.\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Ошибка: стек пуст.\n");
        exit(1);
    }
    return stack->data[stack->top];
}

int getPriority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    Stack stack;
    initialize(&stack);

    int i, j;
    char ch;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (ch == ' ') {
            continue;
        } else if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = ' ';
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);
            } else {
                printf("Ошибка: некорректное выражение.\n");
                return;
            }
        } else {
            while (!isEmpty(&stack) && getPriority(ch) <= getPriority(peek(&stack))) {
                postfix[j++] = ' ';
                postfix[j++] = pop(&stack);
            }
            postfix[j++] = ' ';
            push(&stack, ch);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = ' ';
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}


int evaluatePostfix(char* postfix) {
    Stack stack;
    initialize(&stack);

    int i, result, num = 0;
    char ch;

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (isdigit(ch)) {
            num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--;

            push(&stack, num);
        } else if (ch == ' ') {
            continue;
        } else {
            if (isEmpty(&stack)) {
                printf("Ошибка: недостаточно операндов.\n");
                exit(1);
            }

            int operand2 = pop(&stack);

            if (isEmpty(&stack)) {
                printf("Ошибка: недостаточно операндов.\n");
                exit(1);
            }

            int operand1 = pop(&stack);
            
            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Ошибка: некорректный оператор.\n");
                    exit(1);
            }
            push(&stack, result);
        }
    }

    if (isEmpty(&stack) || stack.top != 0) {
        printf("Ошибка: некорректное выражение.\n");
        exit(1);
    }

    return pop(&stack);
}

// int main() {
//     char infix[MAX_SIZE];
//     char postfix[MAX_SIZE];

//     printf("Infix: ");
//     fgets(infix, MAX_SIZE, stdin);

//     size_t length = strlen(infix);
//     if (infix[length - 1] == '\n') {
//         infix[length - 1] = '\0';
//     }

//     infixToPostfix(infix, postfix);

//     printf("RPN: %s\n", postfix);

//     int result = evaluatePostfix(postfix);

//     printf("result: %d\n", result);

//     return 0;
// }