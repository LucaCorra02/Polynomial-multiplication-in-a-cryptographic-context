#include <stdio.h>
#include <stdlib.h>

const unsigned int look_up_table[] = {0b00,0b01,0b10,0b00};
const unsigned int LSB_I = 0; //la posizione del bit meno significativo
const unsigned int MSB_I = 1; //posizione bit più significativo

unsigned int kth_bit(unsigned int n, unsigned int k);//ritorna il k-esimo bit di n. In modo da non avere array.

void swap_bits(int* n, int p1, int p2);

unsigned int int_to_f3(unsigned int n);

unsigned int abs_f3(int n); //switcha il MSB con il LSB

unsigned int f3_sum(unsigned int a, unsigned int b);

unsigned int f3_prod(unsigned int a, unsigned int b);

void print_binary(unsigned int n);//stampa rappresentazione binaria di un intero.



