#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../getTime.h"

const unsigned int look_up_table[] = {0b00,0b01,0b10,0b00};
const unsigned int LSB_I = 0; //la posizione del bit meno significativo
const unsigned int MSB_I = 1; //posizione bit più significativo

unsigned int int_to_F3(unsigned int n) {
    return n%3;
}

unsigned int kth_bit(unsigned int n, unsigned int k) { //ritorna il k-esimo bit di n. In modo da non avere array.
    return (n & ( 1 << k )) >> k;
}

void print_binary(unsigned int n) { //stampa rappresentazione binaria di un intero.
    unsigned int i, s = 1<<((sizeof(n)<<3)-1);
    printf("%d: ",n);
    for (i = s; i; i>>=1) printf("%d", n & i || 0 );
    printf("\n");
}

unsigned int f3_sum(unsigned int a, unsigned int b){
    /*
     *  print_binary(a);
     *  print_binary(b);
    */
    unsigned int a1 = kth_bit(a,MSB_I), a0 = kth_bit(a,LSB_I), b1 = kth_bit(b,MSB_I), b0 = kth_bit(b,LSB_I);
    unsigned int xor00 = a0^b0;
    unsigned int xor01 = a1^b1;
    unsigned int and00 = a0&b0;
    unsigned int and01 = a1&b1;

    unsigned int sum_lo = ((xor00) ^ (and01)) ^ ((xor01) & (and00));
    unsigned int sum_up = ((xor01) ^ (and00)) ^ ((xor00) & (and01));
    //printf("Ris of sum in binary: s1: %d, s0: %d\n",sum_up,sum_lo);
    return look_up_table[sum_up*2+sum_lo]; //Mod 3
}

unsigned int f3_prod(unsigned int a, unsigned int b){
    /*
     *print_binary(a);
     *print_binary(b);
    */
    unsigned int a1 = kth_bit(a,MSB_I), a0 = kth_bit(a,LSB_I), b1 = kth_bit(b,MSB_I), b0 = kth_bit(b,LSB_I);
    unsigned int and00 = a0&b0;
    unsigned int and03 = a1&b1;
    unsigned int and12 = (and00&and03);

    unsigned int prod_lo = and00 ^ and03 ^ (and12);
    unsigned int prod_up = (a1&b0) ^ (a0&b1) ^ (and12);
    //printf("Ris of product in binary: s1: %d, s0: %d\n",prod_up,prod_lo);
    return look_up_table[prod_up*2+prod_lo]; //Mod 3
}

long double benchmark(unsigned int f3_operation(unsigned int a, unsigned int b),unsigned int num_operations, unsigned int** operations){
    // long double mean_time = 0.0;
    long double total_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;
    int i;

    start_time = get_current_time();
    for(i = 0; i < num_operations; i++){
        //printf("%d %d\n",operations[i][0],operations[i][1]);
        unsigned int ris = f3_operation(int_to_F3(operations[i][0]),int_to_F3(operations[i][1]));
        //printf("%d\n",ris);
    }
    end_time = get_current_time();
    total_time = end_time - start_time;
    //printf("Total time spent: %Lf\n", total_time);
    //mean_time = total_time / (long double) i; //mean time troppo piccolo
    //printf("Mean time spent: %Lf\n", mean_time);
    return total_time;
}


int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
    if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int** operations = create_vector(file_rows, num_operands);
    if (load_vector(argv[1],file_rows, operations) !=0 ){return 1;}

    long double total_time = benchmark(f3_sum, file_rows, operations);
    //long double total_time = benchmark(f3_prod, file_rows, operations);
    printf("Total time spent: %Lf\n", total_time);
    free_vector(operations, file_rows);
    return 0;
}

