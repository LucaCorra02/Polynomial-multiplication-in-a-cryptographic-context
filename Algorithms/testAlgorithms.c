#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

int main() {

    /*
    int p1[] = {1, 2, 3, 4};
    int p2[] = {4, 3, 2, 1};
    int n = 4;
    */
    /*
    int p1[] = {1, 2, 3, 4, 7, 20, 9, 22};
    int p2[] = {4, 3, 2, 1, 10, 5, 3, 10};
    int n = 8;
    */

    // Calcola il prodotto usando Karatsuba
    /*
    int p1[] = {1, 2, 3, 4, 7, 20};
    int p2[] = {4, 3, 2, 1, -10, 5};
    //RIS: 4, 11, 20, 30, 38, 97, 58, 22, -30, -165, 100
    int n = 6;
    /*
    int p1[] = {1, 2, 3, 4, 7, 20, 9, 22, 5, 56, 73, 90, 2, 4, 57, 21};
    int p2[] = {4, 3, 2, 1, 10, 5, 3, 10, 1, 39, 20, 112, 3, 1, 2, 10};
    int n = 16;
    */

    int p1[] = {1, 2, 3, 4, 7, 20};
    int p2[] = {4, 3, 2, 1, -10, 5};
    int n = 6;
    int* result =  karatsuba(n, p1, p2);


    // Stampa il risultato
    printf("Risultato: ");
    for (int i = 0; i < (2 * n) - 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return 0;
}
