#ifndef F9UTILS_H
#define F9UTILS_H

typedef unsigned int f9_element; // 4 bits a3a2a1a0, dove a3a2 rappresentano la parte immaginaria e a1a0 rappresentano la parte reale

unsigned int get_real_part(f9_element element);

unsigned int get_imaginary_part(f9_element element);

void print_f9_element(f9_element n);

f9_element int_to_f9_element(int n);

f9_element get_f9_element(int imaginary, int real);

f9_element f9_sum(f9_element a, f9_element b);

f9_element f9_prod(f9_element a, f9_element b);

f9_element f9_neg(f9_element a);

f9_element f9_prod_img(f9_element a);

#endif //F9UTILS_H
