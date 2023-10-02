#pragma once

#include <stdio.h>

#define MAX_LEN 100

int top = 0;

double arr[MAX_LEN];

void clear() {
  top = 0;
}

void swape_top_2_elements() {
  if(top-1 > 0) {
    double temp = arr[top];
    arr[top] = arr[top-1];
    arr[top-1] = temp;
  }
}

double duplicate_top() {
  if(top+1 < MAX_LEN) {
    arr[top+1] = arr[top];
    ++top;
  }

  return -1;
}

double peek() {
  return arr[top];
}

void push(double value) {
  if(top < MAX_LEN) {
    arr[top++] = value;
  }
}

double pop() {
  if(top < 0)
    return -1;
  return arr[--top];
}
