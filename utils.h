#pragma once

#include <string.h>

#define OPERATORS_COUNT 8
#define MAX_NAME_LEN 10

struct Functions {
  char name[MAX_NAME_LEN];
  int no_of_operands;
  int name_len;
  void* operation;
};

struct Functions operators[] = {
  {"exp", 2, 3, exp_},
  {"sin", 1, 3, sin_},
  {"pow", 2, 3, pow_},
  {"-", 2, 1, sub},
  {"+", 2, 1, add},
  {"/", 2, 1, div_},
  {"*", 2, 1, mul},
  {"%", 2, 1, mod}
};

int is_digit(char c) {
  return (c >= 48 && c <= 57);
}

int isoperator(char c) {
  return (c == '-' || c == '+' || c == '*' || c == '/' || c == '%' || c == '^');
}

struct Functions* is_operator(char* str) {
  int i;

  for(i = 0; i < OPERATORS_COUNT; ++i) {
    if(strncmp(str, operators[i].name, operators[i].name_len) == 0) {
      return &(operators[i]);
    }
  }

  return NULL;
}

int is_char(char c) {
  return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}
