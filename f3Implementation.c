#include "f3Utils.h"

unsigned int int_to_f3(unsigned int n) {
    return look_up_table[n%3];
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
    unsigned int a1 = kth_bit(a,MSB_I), a0 = kth_bit(a,LSB_I), b1 = kth_bit(b,MSB_I), b0 = kth_bit(b,LSB_I);
    unsigned int xor00 = a0^b0;
    unsigned int xor01 = a1^b1;
    unsigned int and00 = a0&b0;
    unsigned int and01 = a1&b1;

    unsigned int sum_lo = ((xor00) ^ (and01)) ^ ((xor01) & (and00));
    unsigned int sum_up = ((xor01) ^ (and00)) ^ ((xor00) & (and01));
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

void swap_bits(int* n, int p1, int p2) {
    if (((*n & (1 << p1)) >> p1) ^ ((*n & (1 << p2)) >> p2)) {
        *n ^= 1 << p1;
        *n ^= 1 << p2;
    }
}

unsigned int abs_f3(int n) { //switcha il MSB con il LSB
    if (n>=0) return int_to_f3(n);
    n = abs(n);
    n = int_to_f3(n);
    swap_bits(&n,MSB_I,LSB_I);
    return n;
}