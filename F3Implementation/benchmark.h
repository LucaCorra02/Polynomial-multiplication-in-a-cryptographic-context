#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "f3UtilsBool.h"

typedef struct {
  long double total_time;
  long double mean_time;
  int result;
} results; // Struttura per ritornare i risultati del benchmark

results benchmark_f3(unsigned int f3_operation(unsigned int a, unsigned int b),unsigned int num_operations, unsigned int** operations);

#endif
