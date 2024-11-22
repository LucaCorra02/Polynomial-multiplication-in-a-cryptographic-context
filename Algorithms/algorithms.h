#ifndef ALGORITMS_H

typedef int* (*NextAlgorithms)(int n, int* p1, int* p2);

int* schoolbook_r(int n, int* p1, int* p2);

int* karatsuba(int n, int* p1, int* p2);

int* unbalanced_karatsuba(int n, int* p1, int* p2);

NextAlgorithms choose_next_algo(int n, int* p1, int* p2);

#define ALGORITMS_H

#endif
