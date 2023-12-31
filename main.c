#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operations.h"
#include "stack.h"
#include "variables.h"
#include "utils.h"

#define MAX_EXP_LEN 1000

double last_printed_value = 0;

double eval(double operands[], struct Functions* operator);

int getname(char name[], int start, char out[]) {
  int i = 0;

  while(name[start] != ' ' && name[start] != '\t' && name[start] != '\0' && name[start] != '(') {
    out[i] = name[start];
    ++start;
    ++i;
  }

  out[i] = '\0';

  return start;
}

double parse_input(char input[]) {
  int i = 0;

    while(input[i] != '\0') {
      if((input[i] == '-' && (i+1) < strlen(input) && is_digit(input[i+1])) || is_digit(input[i])) {
	double final = 0;
	int has_prec = 0, no_of_0 = 1, has_sign = 0;

	if(input[i] == '-') {
	  ++i;
	  has_sign = 1;
	}

	while(input[i] != ' ' && input[i] != '\0' && input[i] != '\t' && !isoperator(input[i])) {
	  if(input[i] == '.') {
	    has_prec = 1;
	    ++i;
	    continue;
	  }
	  final = (final*10) + (input[i] - '0');
	  if(has_prec) {
	    no_of_0 *= 10;
	  }
	  ++i;
	}
	
	if(has_prec) {
	  final /= no_of_0;
	  has_prec = 0;
	}

	if(has_sign) {
	  final *= -1;
	}

	push(final);
      }
      else {
	char op_name[MAX_NAME_LEN];
	memset(op_name, 0, MAX_NAME_LEN);

	int end = getname(input, i, op_name);
	struct Functions *found_operator = NULL;

	if((found_operator = is_operator(op_name)) != NULL) {
	  int c = 0;
	  double* operands = (double*)malloc(sizeof(double)*found_operator->no_of_operands);

	  for(c = found_operator->no_of_operands-1; c >= 0; --c) {
	    operands[c] = pop();
	  }

	  double result = eval(operands, found_operator);
	  push(result);
	}
      }
      ++i;
    }

    return pop();
}

int main(int argc, char** argv) {
  if(argc == 2) {
    double result = parse_input(argv[1]);
    fprintf(stdout, "%0.2f\n", result);
    return 0;
  }

  int is_running = 1;
  char buffer[MAX_EXP_LEN];
  memset(buffer, 0, MAX_EXP_LEN);

  int c = 0, i = 0, is_variable_set = 0, equal_sign_index = 0;
  char variable_name = '_';

  do {
    fprintf(stdout, ">>> ");
    while((c = getchar()) != EOF) {
      if(c == '\n' || i == MAX_EXP_LEN) {
	i = 0;
	break;
      }
      else {
	if(is_char(c) && is_variable_set == 0) {
	  is_variable_set = 1;
	  variable_name = c;
	}
	else if(c == '=' && is_variable_set) {
	  equal_sign_index = i+1;
	}
	buffer[i++] = c;
      }
    }

    char variable_char = -1;

    if(strncmp(buffer, "quit", 4) == 0) {
      is_running = 0;
    }
    else if(strncmp(buffer, "_", 1) == 0) {
      fprintf(stdout, "%0.2f\n", last_printed_value);
    }
    else if((variable_char = is_variable(buffer)) != -1) {
      double var_value = get_variable_value(variable_char);
      fprintf(stdout, "%0.2f\n", var_value);
      equal_sign_index = 0;
      memset(buffer, 0, MAX_EXP_LEN);
      is_variable_set = 0;
      last_printed_value = var_value;
    }
    else {
      double result = parse_input(buffer+equal_sign_index);
      if(is_variable_set) {
	is_variable_set = 0;
	set_var_value(variable_name, result);
      }
      fprintf(stdout, "%0.2f\n", result);
      last_printed_value = result;
      memset(buffer, 0, MAX_EXP_LEN);
    }
  }
  while(is_running);

  return 0;
}

typedef double (*operation_t)(double[]);

double eval(double operands[], struct Functions* operator) {
  operation_t arth_operation = (operation_t)(operator->operation);
  return arth_operation(operands);
}
