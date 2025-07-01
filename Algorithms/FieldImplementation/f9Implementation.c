#include "f3Utils.h"
#include "f9Utils.h"

typedef unsigned int f9_element; // 4 bits a3a2a1a0, dove a3a2 rappresentano la parte immaginaria e a1a0 rappresentano la parte reale
const unsigned int look_up_sum_f9[] = {0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,1,2,0,1,5,6,4,5,9,10,8,9,1,2,0,1,2,0,1,2,6,4,5,6,10,8,9,10,2,0,1,2,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,4,5,6,4,5,6,4,5,9,10,8,9,1,2,0,1,5,6,4,5,6,4,5,6,10,8,9,10,2,0,1,2,6,4,5,6,4,5,6,4,8,9,10,8,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,4,5,6,4,8,9,10,8,9,10,8,9,1,2,0,1,5,6,4,5,9,10,8,9,10,8,9,10,2,0,1,2,6,4,5,6,10,8,9,10,8,9,10,8,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,1,2,0,1,5,6,4,5,9,10,8,9,1,2,0,1,2,0,1,2,6,4,5,6,10,8,9,10,2,0,1,2,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0};
const unsigned int look_up_prod_f9[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,0,2,1,0,8,10,9,8,4,6,5,4,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,0,2,6,10,2,1,5,9,1,0,4,8,0,0,5,10,0,6,8,1,6,9,2,4,9,0,5,10,0,0,6,9,0,10,1,4,10,5,8,2,5,0,6,9,0,0,4,8,0,2,6,10,2,1,5,9,1,0,4,8,0,0,8,4,0,1,9,5,1,2,10,6,2,0,8,4,0,0,9,6,0,5,2,8,5,10,4,1,10,0,9,6,0,0,10,5,0,9,4,2,9,6,1,8,6,0,10,5,0,0,8,4,0,1,9,5,1,2,10,6,2,0,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,4,5,6,4,8,9,10,8,0,1,2,0,0,2,1,0,8,10,9,8,4,6,5,4,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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
    return look_up_sum_f9[a<<4 | b];
}

f9_element f9_prod(f9_element a, f9_element b) {
    /*unsigned int a1 = get_imaginary_part(a), a0 = get_real_part(a);
    unsigned int b1 = get_imaginary_part(b), b0 = get_real_part(b);
    return (f3_sum(f3_prod(a0,b1),f3_prod(a1,b0)) << 2 ) | f3_sum(f3_prod(a0,b0), swap_bits(f3_prod(a1,b1)));*/
    return look_up_prod_f9[a<<4 | b];
}

f9_element f9_neg(f9_element a){
    return get_f9_element(swap_bits(get_imaginary_part(a)), swap_bits(get_real_part(a)));
}

f9_element f9_prod_img(f9_element a){
    return get_f9_element(get_real_part(a), swap_bits(get_imaginary_part(a)));
}

f9_element f9_prod_img_neg(f9_element a){
    return get_f9_element(swap_bits(get_real_part(a)), get_imaginary_part(a));
}