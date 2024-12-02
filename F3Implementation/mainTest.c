#include <stdio.h>
#include <stdlib.h>
#include "benchmark.h"
#include "f3Utils.h"
#include "../utils.h"


void testFile(unsigned int f3_operation(unsigned int a, unsigned int b),unsigned int file_rows, unsigned int** operations){
    results ris = benchmark_f3(f3_operation, file_rows, operations);
}

void bench(unsigned int f3_operation(unsigned int a, unsigned int b),unsigned int file_rows, unsigned int** operations){
    int rip = 200;
    for (int i = 1; i <= rip; i++) {
        results ris = benchmark_f3(f3_operation, file_rows, operations);
        printf("Esecuzione: %d %d Mean Time %.14Lf -> Total time spent: %Lf\n", i ,ris.result, ris.mean_time , ris.total_time);
    }
}

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
    if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }

    // ./mainTest.out ../TestFile/Cifra1/inputTest.txt 1000000 2 > ../BenchMark/Cifra1/sumIntV1.txt
    // python3 ../BenchMark/calc.py ../BenchMark/Cifra1/sumIntV1.txt

    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int** operations = create_vector(file_rows, num_operands);
    if (load_vector(argv[1], file_rows, operations) !=0 ){ return 1; }
    printf("op: %d\n",operations[0][0]);

    //testFile(f3_sum, file_rows, operations);
    //printf("ciao");
    //testFile(f3_prod, file_rows, operations);

    //bench(f3_sum, file_rows, operations);
    bench(f3_prod, file_rows, operations);



    free_vector(operations, file_rows);
    return 0;
}