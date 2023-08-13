#include "modules.h"

/*STR*/

void init_str_stack(Stack* stack) { stack->top = -1; }

bool is_empty_str(Stack* stack) { return stack->top == -1; }

bool is_full_str(Stack* stack) { return stack->top >= MAX_SIZE - 1; }

void push_str(Stack* stack, char element) {
  if (!(is_full_str(stack))) stack->data[++stack->top] = element;
}

void push_func(Stack* stack, char* element) {
  if (!(is_full_str(stack))) {
    for (int i = (strlen(element) - 1); i >= 0; i--) {
      stack->data[++stack->top] = element[i];
    }
  }
}

char pop_str(Stack* stack) {
  if (is_empty_str(stack)) return 0;
  return stack->data[stack->top--];
}

char peek_str(Stack* stack) {
  if (is_empty_str(stack)) return 0;
  return stack->data[stack->top];
}

/*NUM*/

void init_num_stack(NumStack* stack) { stack->top = -1; }

bool is_empty_num(NumStack* stack) { return stack->top == -1; }

bool is_full_num(NumStack* stack) { return stack->top >= MAX_SIZE - 1; }

void push_num(NumStack* stack, long double num) {
  if (!is_full_num(stack)) stack->data[++stack->top] = num;
}

long double pop_num(NumStack* stack) {
  if (is_empty_num(stack)) return 0;
  return stack->data[stack->top--];
}
