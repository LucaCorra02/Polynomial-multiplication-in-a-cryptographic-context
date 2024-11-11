#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "getTime.h"
#include "utils.h"

/*
    TODO : metodo chw switcha i bit ( fa il meno) .
    TODO : valgrind massif
    gcc -O3 basicOperationBool.c -o basicOperationBool
    time ./basicOperationBool TestFile/testLowNumber.txt 1000000 2 > TestFile/outputSumLowNumber.txt
*/

#define CHECK_BIT(n,pos) ((n) & (1<<(pos))) //macro per controllare se l'n-esimo bit è settato.

const unsigned int LSB_I = 0; //la posizione del bit meno significativo
const unsigned int MSB_I = 1; //posizione bit più significativo
const unsigned int look_up_table[] = {0b00,0b01,0b10,0b00};
typedef struct f3_element {bool bits[2];} f3_element; //Passo tutto per copia usando lo stack, più effecente che allocare sullo heap.
// Incapsulo l'array in una struct in quanto è più comodo da passare alle funzioni.

unsigned int f3_to_int(f3_element f3) {
    return look_up_table[f3.bits[MSB_I]*2+f3.bits[LSB_I]];
}

f3_element int_to_f3(unsigned int n){
    n = n%3;
    f3_element element;
    element.bits[0] = 0, element.bits[1] = 0;
    if (CHECK_BIT(n, MSB_I)) element.bits[MSB_I] = 1;
    if (CHECK_BIT(n, LSB_I)) element.bits[LSB_I] = 1;
    return element;
}

void print_f3_element(f3_element f3){
  printf("msb: %d, lsb: %d\n",f3.bits[MSB_I],f3.bits[LSB_I]);
}

void print_binary(unsigned int n) { //stampa rappresentazione binaria di un intero.
    unsigned int i, s = 1<<((sizeof(n)<<3)-1);
    printf("%d: ",n);
    for (i = s; i; i>>=1) printf("%d", n & i || 0 );
    printf("\n");
}

f3_element f3_sum(f3_element a, f3_element b){
    f3_element ris;
    bool xor00 = a.bits[LSB_I] ^ b.bits[LSB_I];
    bool xor01 = a.bits[MSB_I] ^ b.bits[MSB_I];
    bool and00 = a.bits[LSB_I] & b.bits[LSB_I];
    bool and01 = a.bits[MSB_I] & b.bits[MSB_I];

    bool sum_lo = ((xor00) ^ (and01)) ^ ((xor01) & (and00));
    bool sum_up = ((xor01) ^ (and00)) ^ ((xor00) & (and01));
    ris.bits[MSB_I] = sum_up, ris.bits[LSB_I] = sum_lo;
    return ris; //Mod 3;
}

f3_element f3_prod(f3_element a, f3_element b){
    f3_element ris;
    bool and00 = a.bits[LSB_I] & b.bits[LSB_I];
    bool and03 = a.bits[MSB_I] & b.bits[MSB_I];
    bool and12 = (and00&and03);

    unsigned int prod_lo = and00 ^ and03 ^ (and12);
    unsigned int prod_up = (a.bits[MSB_I] & b.bits[LSB_I]) ^ (a.bits[LSB_I] & b.bits[MSB_I]) ^ (and12);
    ris.bits[MSB_I] = prod_up, ris.bits[LSB_I] = prod_lo;
    return ris; //Mod 3
}

long double benchmark(f3_element f3_operation(f3_element a, f3_element b),unsigned int num_operations, unsigned int operands, unsigned int operations[num_operations][operands])
{
    //long double mean_time = 0.0;
    long double total_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;
    int i;

    start_time = get_current_time();
    for(i = 0; i < num_operations; i++){
        //printf("bool %d %d\n",operations[i][0],operations[i][1]);
        f3_element ris = f3_operation(int_to_f3(operations[i][0]),int_to_f3(operations[i][1]));
        //printf("%d\n",f3_to_int(ris));
    }
    end_time = get_current_time();
    total_time = end_time - start_time;
    // printf("Total time spent: %Lf\n", total_time);
    // mean_time = total_time / (long double) i; //mean time troppo piccolo
    // printf("Mean time spent: %Lf\n", mean_time);
    return total_time;
}

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
    if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int operations[file_rows][num_operands];
    int ris = load_vector(argv[1],file_rows,num_operands, operations); //carico i dati da file in un array bidemensionale
    if (ris != 0){return 1;}
    //long double total_time = benchmark(f3_sum, file_rows, num_operands, operations);
    long double total_time = benchmark(f3_prod, file_rows, num_operands, operations);
    printf("%Lfs\n", total_time);
    return 0;
}
