#include "f3Utils.h"

const unsigned int look_up_table[] = {0b00,0b01,0b10,0b00};
const unsigned int swap_look_up_table[] = {0b00,0b10,0b01,0b00};
const unsigned int LSB_I = 0; //la posizione del bit meno significativo
const unsigned int MSB_I = 1; //posizione bit più significativo

unsigned int mod (int a, int b) { // a mod b. con b >= 0
    return ((a % b) + b) % b;
}

unsigned int int_to_f3(int n) {
    return ( n >= 0 ) ? n%3 : mod(n, 3);
}

unsigned int kth_bit(unsigned int n, unsigned int k) { //ritorna il k-esimo bit di n. In modo da non avere array. 3 operazioni
    return (k == MSB_I) ? (*(char*)&n & 2) >> 1 : *(char*)&n & 1;
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
    return look_up_table[sum_up^sum_lo]; //Mod 3
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

unsigned int swap_bits(unsigned int n){  return swap_look_up_table[n]; }

/*
void swap_bits(int* n, int p1, int p2) { //switcha il MSB con il LSB //Costo per swap_bit da segnalare, non è zero.
    if (((*n & (1 << p1)) >> p1) ^ ((*n & (1 << p2)) >> p2)) {
        *n ^= 1 << p1;
        *n ^= 1 << p2;
    }
}*/