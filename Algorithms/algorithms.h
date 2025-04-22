#ifndef ALGORITMS_H
#include "algoUtils.h"

/* SCHOOLBOOK ALGO */
int* schoolbook_f3(int n, int* p1, int* p2);

f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2);

/* KARATSUBA ALGO */
void polynomial_sum_f3(int* p1, int len_p1, int* p2, int len_p2, int* ris);

int* unbalanced_karatsuba_f3(int n, int* p1, int* p2);

void polynomial_sum_f9(f9_element* p1, int len_p1, f9_element* p2, int len_p2, f9_element* ris);

f9_element* unbalanced_karatsuba_f9(int n, f9_element* p1, f9_element* p2);

/* 3_SPLIT_V1 ALGO */
int* split_3_f3(int m, int* p1, int* p2);

f9_element* split_3_f9(int m, f9_element* p1, f9_element* p2);

/* 3_SPLIT_V2 ALGO*/
int* split_3_v2_f3(int m, int* p1, int* p2);

f9_element* split_3_v2_f9(int m, f9_element* p1, f9_element* p2);


/* 4_SPLIT_V2 ALGO */
int* split_4_f3(int m, int* p1, int* p2);

f9_element* split_4_f9(int m, f9_element* p1, f9_element* p2);

/* 5_SPLIT ALGO */

f9_element* split_5_f9(int m, f9_element* p1, f9_element* p2);


#endif
