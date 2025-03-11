#include <stdio.h>
#include <stdlib.h>
#include "f3bits.h"
#include  "f3Utils.h"

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
    unsigned int a1 = kth_bit(a,LSB_I), a0 = kth_bit(a,MSB_I), b1 = kth_bit(b,LSB_I), b0 = kth_bit(b,MSB_I);
    unsigned int and00 = a0&b0;
    unsigned int and03 = a1&b1;
    unsigned int and12 = (and00&and03);

    unsigned int prod_lo = and00 ^ and03 ^ (and12);
    unsigned int prod_up = (a1&b0) ^ (a0&b1) ^ (and12);
    return look_up_table[prod_up*2+prod_lo]; //Mod 3
}

