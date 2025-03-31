#ifndef KARATSUBAFIELD_H
#define KARATSUBAFIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../FieldImplementation/f3Utils.h"
#include "../FieldImplementation/F9Utils.h"

int* karatsuba_f3(int n, int* p1, int* p2);

void polynomial_sum(int* p1, int len_p1, int* p2, int len_p2, int* ris);

int* unbalanced_karatsuba(int n, int* p1, int* p2);

void polynomial_sum_f3(int* p1, int len_p1, int* p2, int len_p2, int* ris);

int* unbalanced_karatsuba_f3(int n, int* p1, int* p2);

void polynomial_sum_f9(f9_element* p1, int len_p1, f9_element* p2, int len_p2, f9_element* ris);

f9_element* unbalanced_karatsuba_f9(int n, f9_element* p1, f9_element* p2);

#endif //KARATSUBAFIELD_H
