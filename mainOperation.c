#include "f3Utils.h"
#include "getTime.h"
#include "utils.h"
#include "f9Utils.h"

long double benchmark(f9_element f9_operation(f9_element a, f9_element b),unsigned int num_operations, unsigned int** operations){
    long double total_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;
    int i;

    start_time = get_current_time();
    for (i=0; i < num_operations; i++) {
        f9_element a = get_f9_element(operations[i][0],operations[i][1]);
        f9_element b = get_f9_element(operations[i][2],operations[i][3]);
        f9_element ris = f9_prod(a,b);
        //print_f9_element(ris);
    }
    end_time = get_current_time();
    total_time = end_time - start_time;
    return total_time;
}

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
    if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int** operations = create_vector(file_rows, num_operands);

    if (read_file(argv[1],file_rows,operations) != 0) return 1;
    long double total_time = benchmark(f9_prod,file_rows, operations);
    printf("%Lfs\n", total_time);
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