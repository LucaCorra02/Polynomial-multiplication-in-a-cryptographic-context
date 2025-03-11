#include "f9Benchmark.h"
#include "f9Utils.h"
#include "getTime.h"

results benchmark_f9(f9_element f9_operation(f9_element a, f9_element b),unsigned int num_operations, unsigned int** operations){
    long double total_time = 0.0;
    long double mean_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;
    int i;
    unsigned int total_ris = 0;
    start_time = get_current_time();
    for (i=0; i < num_operations; i++) {
        f9_element a = get_f9_element(operations[i][0],operations[i][1]);
        f9_element b = get_f9_element(operations[i][2],operations[i][3]);
        f9_element ris = f9_operation(a,b);
        total_ris += ris;
        print_f9_element(ris);
    }
    end_time = get_current_time();
    total_time = end_time - start_time;
    mean_time = total_time / (long double) num_operations;
    results results = {total_time, mean_time, total_ris};
    return results;

}
