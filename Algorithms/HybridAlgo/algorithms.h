#ifndef ALGORITMS_H
#include "../algoUtils.h"

/* SCHOOLBOOK ALGO */
int* schoolbook_f3(int n, int* p1, int* p2);

f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2);

/* KARATSUBA ALGO */
int* karatsuba_f3(int n, int* p1, int* p2);

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

/* 4_SPLIT_V1 ALGO */
int* split_4_v1_f3(int m, int* p1, int* p2);

f9_element* split_4_v1_f9(int m, f9_element* p1, f9_element* p2);

/* 4_SPLIT_V2 ALGO */
int* split_4_f3(int m, int* p1, int* p2);

f9_element* split_4_f9(int m, f9_element* p1, f9_element* p2);

/* 5_SPLIT ALGO */
int* split_5_f3(int m, int* p1, int* p2);

f9_element* split_5_f9(int m, f9_element* p1, f9_element* p2);

/* READ FILE BEST DEGREE*/
typedef int* (*NextAlgoF3)(int n, int* p1, int* p2);

extern NextAlgoF3 look_up_table_sign_f3[7];

typedef f9_element* (*NextAlgoF9)(int n, f9_element* p1, f9_element* p2);

extern NextAlgoF9 look_up_table_sign_f9[7];

extern int* list_f3;

void read_file_f3(char* file_name, int dim_file);

NextAlgoF3 choose_next_algo_f3(int n);

extern int* list_f9;

void read_file_f9(char* file_name, int dim_file);

NextAlgoF9 choose_next_algo_f9(int n);

#endif
