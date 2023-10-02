#pragma once

#include <math.h>

double exp_(double params[]) {
  return exp(params[0]);
}

double pow_(double params[]) {
  return pow(params[0], params[1]);
}

double sin_(double params[]) {
  return sin(params[0]);
}

double add(double params[]) {
  return params[0] + params[1];
}

double sub(double params[]) {
  return params[0] - params[1];
}

double mul(double params[]) {
  return params[0] * params[1];
}

double div_(double params[]) {
  return params[0] / params[1];
}

double mod(double params[]) {
  return ((int)params[0]) % ((int)params[1]);
}
