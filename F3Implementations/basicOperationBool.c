#include <stdio.h>
#include <stdbool.h>
#include "f3bool.h"
#include "f3Utils.h"

unsigned int f3_to_int_bool(f3_element f3){
    return look_up_table[f3.bits[MSB_I]*2+f3.bits[LSB_I]];
}

f3_element int_to_f3_bool(unsigned int n){
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

void print_binary_bool(unsigned int n){
    unsigned int i, s = 1<<((sizeof(n)<<3)-1);
    printf("%d: ",n);
    for (i = s; i; i>>=1) printf("%d", n & i || 0 );
    printf("\n");
}

f3_element f3_sum_bool(f3_element a, f3_element b){
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

f3_element f3_prod_bool(f3_element a, f3_element b){
    f3_element ris;
    bool and00 = a.bits[LSB_I] & b.bits[LSB_I];
    bool and03 = a.bits[MSB_I] & b.bits[MSB_I];
    bool and12 = (and00&and03);

    unsigned int prod_lo = and00 ^ and03 ^ (and12);
    unsigned int prod_up = (a.bits[MSB_I] & b.bits[LSB_I]) ^ (a.bits[LSB_I] & b.bits[MSB_I]) ^ (and12);
    ris.bits[MSB_I] = prod_up, ris.bits[LSB_I] = prod_lo;
    return ris; //Mod 3
}