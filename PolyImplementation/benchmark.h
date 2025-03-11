#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "f9Utils.h"

typedef struct {
    long double total_time;
    long double mean_time;
    int result;
} results; // Struttura per ritornare i risultati del benchmark

results benchmark_f9(f9_element f9_operation(f9_element a, f9_element b),unsigned int num_operations, unsigned int** operations);

#endif //BENCHMARK_H
