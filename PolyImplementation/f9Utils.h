#ifndef F9UTILS_H
#define F9UTILS_H

typedef unsigned int f9_element; // 4 bits a3a2a1a0, dove a3a2 rappresentano la parte immaginaria e a1a0 rappresentano la parte reale

unsigned int get_real_part(f9_element element);

unsigned int get_imaginary_part(f9_element element);

void print_f9_element(f9_element n);

f9_element get_f9_element(int imaginary, int real);

f9_element f9_sum(f9_element a, f9_element b);

f9_element f9_prod(f9_element a, f9_element b);

#endif //F9UTILS_H
