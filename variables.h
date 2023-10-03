#pragma once

#include <string.h>
#include <stdio.h>

#include "utils.h"

#define NVARS 26

/* 
   NOTE:
   for now we will not support variables in expressions
*/

double variables[NVARS];

int is_char_lower(char c) {
  return (c >= 97 && c <= 122);
}

char is_variable(char s[]) {
  int len = strlen(s);

  if(len == 1 && is_char(s[0])) {
    return s[0];
  }

  return -1;
}

// variable names are case insensitive
double get_variable_value(char var_name) {
  if(is_char_lower(var_name)) {
    return variables[var_name - 'a'];
  }

  return variables[var_name - 'A'];
}

void set_var_value(char var_name, double value) {
  if(is_char_lower(var_name)) {
    variables[var_name - 'a'] = value;
  }
  else {
    variables[var_name - 'A'] = value;
  }
}
