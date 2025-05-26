#include "f3Utils.h"
#include "utils.h"
#include "f9Utils.h"
#include "f9Benchmark.h"

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
    if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int** operations = create_vector(file_rows, num_operands);

    if (read_file(argv[1],file_rows,operations) != 0) return 1;

    for (unsigned int i = 0; i < 3; i++) {
        results ris = benchmark_f9(f9_prod,file_rows, operations);
        //printf("Esecuzione: %d %d Mean Time %.14Lf -> Total time spent: %Lf\n", i ,ris.result, ris.mean_time , ris.total_time);
    }
    free_vector(operations, file_rows);

    /*
        Con *(char*)&a ottengo il puntatore (1 byte) al byte meno significativo (intero a 32 bit è su 4 byte).
        Eseguo una maschera 0...01 per esterra il LSB.

        unsigned int a = 1;
        printf("MSB: %d\n",(*(char*)&a & 2) >> 1);
        printf("LSB: %d\n",*(char*)&a & 1);

        int n = 3;
        swap_bits(&n,1,0);
        print_binary(n);

     */

    return 0;
}