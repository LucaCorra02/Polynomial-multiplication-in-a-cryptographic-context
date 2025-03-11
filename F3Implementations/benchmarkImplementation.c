#include "benchmarkf3.h"
#include "f3bits.h"
#include "../getTime.h"
#include <stdio.h>
#include <stdlib.h>

results benchmark_f3(unsigned int f3_operation(unsigned int a, unsigned int b),unsigned int num_operations, unsigned int** operations){
    long double mean_time = 0.0;
    long double total_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;

    start_time = get_current_time();
    unsigned int total_ris = 0;
    for(unsigned int i = 0; i < num_operations; i++){
        //printf("%d %d\n",operations[i][0],operations[i][1]);
        unsigned int ris = f3_operation(int_to_F3(operations[i][0]),int_to_F3(operations[i][1]));
        //printf("%d\n",ris);
        total_ris += ris;
    }
    end_time = get_current_time();
    total_time = end_time - start_time;
    mean_time = total_time / (long double) num_operations;
    results results = {total_time, mean_time, total_ris};
    return results;
}