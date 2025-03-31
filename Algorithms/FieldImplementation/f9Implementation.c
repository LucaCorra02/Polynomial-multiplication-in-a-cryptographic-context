#include "f3Utils.h"
#include "f9Utils.h"

typedef unsigned int f9_element; // 4 bits a3a2a1a0, dove a3a2 rappresentano la parte immaginaria e a1a0 rappresentano la parte reale

unsigned int get_real_part(f9_element element){
    return kth_bit(element,1)*2 + kth_bit(element,0);
}

unsigned int get_imaginary_part(f9_element element){
    return element >> 2; //Shift a destra di due
}

void print_f9_element(f9_element n) {
    printf("%dw + %d\n",get_imaginary_part(n),get_real_part(n));
}

f9_element int_to_f9_element(int n){
    unsigned int real_part = n & 0b11;
    unsigned int img_part = (n >> 2) & 0b11;
    return get_f9_element(img_part,real_part);
}

f9_element get_f9_element(int imaginary, int real) {
    imaginary = int_to_f3(imaginary);
    real = int_to_f3(real);
    return (imaginary << 2) | real; // Shifto di 2 la parte immaginaria e poi metto in or la parte reale
}

f9_element f9_sum(f9_element a, f9_element b) {
    return (f3_sum(get_imaginary_part(a) , get_imaginary_part(b)) << 2 ) | f3_sum(get_real_part(a) , get_real_part(b));
}

f9_element f9_prod(f9_element a, f9_element b) {
    unsigned int a1 = get_imaginary_part(a), a0 = get_real_part(a);
    unsigned int b1 = get_imaginary_part(b), b0 = get_real_part(b);
    return (f3_sum(f3_prod(a0,b1),f3_prod(a1,b0)) << 2 ) | f3_sum(f3_prod(a0,b0), swap_bits(f3_prod(a1,b1)));
}

f9_element f9_neg(f9_element a){
    return get_f9_element(swap_bits(get_imaginary_part(a)), swap_bits(get_real_part(a)));
}