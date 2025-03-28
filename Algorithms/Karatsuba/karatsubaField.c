#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../FieldImplementation/f3Utils.h"


int* karatsuba_f3(int n, int* p1, int* p2) {
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloco spazio per il risultato
    if (n == 1) { ris[0] = f3_prod(int_to_f3(p1[0]) , int_to_f3(p2[0])); return ris; } // Caso Base
    int k = n / 2; // Suddivisione a metà
    int* a0 = p1;
    int* a1 = p1 + k;
    int* b0 = p2;
    int* b1 = p2 + k;

    int* a0a1 = calloc(k, sizeof(unsigned int)); // Alloco spazio per la somma
    int* b0b1 = calloc(k, sizeof(unsigned int));
    for (int i = 0; i < k; i++) {
        a0a1[i] = f3_sum(int_to_f3(a0[i]), int_to_f3(a1[i]));
        b0b1[i] = f3_sum(int_to_f3(b0[i]), int_to_f3(b1[i]));
    }

    int* P0 = karatsuba_f3(k, a0, b0); // Parte sinistra
    int* P2 = karatsuba_f3(k, a1, b1); // Parte destra
    int* P1 = karatsuba_f3(k, a0a1, b0b1); //Parte centrale

    int dim = (2 * k) - 1;
    for (int j = 0; j < dim; j++) {
        P1[j] = f3_sum(int_to_f3(P1[j]), f3_prod(f3_sum(int_to_f3(P0[j]), int_to_f3(P2[j])),2));
    }

    for (int i = 0; i < dim; i++) {
        ris[i] = f3_sum(int_to_f3(ris[i]) ,int_to_f3(P0[i]));
        ris[i + k] = f3_sum(int_to_f3(ris[i + k]), int_to_f3(P1[i])); // Shift di k
        ris[i + (2 * k)] = f3_sum(int_to_f3(ris[i + (2 * k)]), int_to_f3(P2[i])); // Shift di 2*k
    }

    // Libero la memoria allocata
    free(a0a1);
    free(b0b1);
    free(P0);
    free(P2);
    free(P1);
    return ris;
}

int* karatsuba(int n, int* p1, int* p2) {
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloco spazio per il risultato
    if (n == 1) { ris[0] = p1[0] * p2[0]; return ris; } // Caso Base
    int k = n / 2; // Suddivisione a metà
    int* a0 = p1;
    int* a1 = p1 + k;
    int* b0 = p2;
    int* b1 = p2 + k;

    int* a0a1 = calloc(k, sizeof(int)); // Alloco spazio per la somma
    int* b0b1 = calloc(k, sizeof(int));
    for (int i = 0; i < k; i++) {
        a0a1[i] = a0[i] + ((i < n - k) ? a1[i] : 0);
        b0b1[i] = b0[i] + ((i < n - k) ? b1[i] : 0);
    }

    int* P0 = karatsuba(k, a0, b0); // Parte sinistra
    int* P2 = karatsuba(k, a1, b1); // Parte destra
    int* P1 = karatsuba(k, a0a1, b0b1); //Parte centrale

    int dim = (2 * k) - 1;
    for (int j = 0; j < dim; j++) {
        P1[j] -= (P0[j] + P2[j]);
    }

    for (int i = 0; i < dim; i++) {
        ris[i] += P0[i];
        ris[i + k] += P1[i]; // Shift di k
        ris[i + (2 * k)] += P2[i]; // Shift di 2*k
    }

    // Libero la memoria allocata
    free(a0a1);
    free(b0b1);
    free(P0);
    free(P2);
    free(P1);
    return ris;
}

void polynomial_sum(int* p1, int len_p1, int* p2, int len_p2, int* ris) { // Somma per polinomi sbilanciati
    for (int i = 0; i < len_p1; i++) ris[i] = p1[i];
    for (int i = 0; i < len_p2; i++) ris[i] += p2[i];
}

int* unbalanced_karatsuba(int n, int* p1, int* p2) {
    int* result = calloc((2 * n) - 1, sizeof(int)); // Alloco risultato
    if (n == 1) { result[0] = p1[0] * p2[0]; return result; } // Caso base

    int k = n / 2;
    int mid = n - k; // Resto divisione
    int* a0 = p1;
    int* a1 = p1 + mid; // a1 ha meno terimi rispetto ad a0
    int* b0 = p2;
    int* b1 = p2 + mid;
    int size_a1 = n - mid, size_b1 = n - mid;

    int* a0a1 = calloc(mid, sizeof(int));
    int* b0b1 = calloc(mid, sizeof(int));
    polynomial_sum(a0, mid, a1, size_a1, a0a1);
    polynomial_sum(b0, mid, b1, size_b1, b0b1);

    int* P0 = unbalanced_karatsuba(mid, a0, b0); // P0 = A0 * B0
    int* P2 = unbalanced_karatsuba(size_a1, a1, b1); // P2 = A1 * B1
    int* P1 = unbalanced_karatsuba(mid, a0a1, b0b1); // P1 = (A0 + A1) * (B0 + B1)

    for (int i = 0; i < (2 * mid ) - 1; i++){ P1[i] -= P0[i]; } // P1 = P1 - P0
    for (int i = 0; i < (2 * size_a1) - 1; i++) { P1[i] -= P2[i]; } // P1 = (P1 - P0) - P0

    //Combini i risultati
    for (int i = 0; i < (2 * mid ) - 1; i++) {
        result[i] += P0[i]; // Termini da 0 a mid-1
        result[i + mid] += P1[i]; // Terimini da mid a (2*mid)-1
    }
    for (int i = 0; i < (2 * size_a1) - 1; i++) {
        result[i + (2 * mid)] += P2[i]; // Termini da (2*mid) a n-1
    }

    free(a0a1);
    free(b0b1);
    free(P0);
    free(P1);
    free(P2);
    return result;
}

int* split_operands(char* p, int num_operands){
    int i = 0;
    int* ris = calloc(num_operands,sizeof(int));
    char* token = strtok(p, ",");
    while(token != NULL && i < num_operands) {
        ris[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return ris;
}

void print_vector(int* v, int num_elements){
    for (int i = 0; i < num_elements-1; i++){
        printf("%d,",v[i]);
    }
    printf("%d\n",v[num_elements-1]);
}

#define BUFFERSIZE 3000;
#define NUM_OPERANDS 33;

int main(int argc, char *argv[]){

    int num_operands = NUM_OPERANDS;
    int buffer_size = BUFFERSIZE;

    char buffer[buffer_size];
    while (fgets(buffer, buffer_size , stdin)){
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        int* p1 = split_operands(left, num_operands);
        int* p2 = split_operands(right, num_operands);
        int* ris = unbalanced_karatsuba(num_operands, p1, p2);
        print_vector(ris, (2*num_operands)-1);
        free(p1);
        free(p2);
        free(ris);
    }

    return 0;
}