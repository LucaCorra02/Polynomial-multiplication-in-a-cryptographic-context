#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    cd ..
    make all
    cd Schoolbook
    ./schoolbook.out ../PolyTest/TestFile/LowDeg/lowDeg.txt 10000 10
 */

int* schoolbook_recursive(int n, int* p1, int* p2, int* ris){
    if(n==0){return ris;} //caso di uscita
    int max_deg = n - 1;
    int mst_p1 = p1[max_deg]; //termine di grado massimo
    int mst_p2 = p2[max_deg];
    ris[max_deg * 2] += mst_p1 * mst_p2;

    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p1 * p2[i];
    }
    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p2 * p1[i];
    }
    return schoolbook_recursive(n - 1, p1, p2, ris);
}

int* schoolbook_r(int n, int* p1, int* p2) { //n = numero di termini.
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloca e inizializza.
    if (n==1) {ris[0] = p1[0] * p2[0]; return ris;} // Caso base, evito la chimata ricorsiva.
    return schoolbook_recursive(n, p1, p2, ris);
}

void print_poly(int* ris, int n){
    for (int i = 0; i < n-1; i++){
        printf("%d, ", ris[i]);
    }
    printf("%d\n",ris[n-1]);
}


typedef int* (*NextAlgorithms)(int n, int* p1, int* p2);

/*
    Algoritmo di Karatsuba, Requisiti :
     - n deve essere pari.
 */
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
        a0a1[i] = a0[i] + a1[i];
        b0b1[i] = b0[i] + b1[i];
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

void polynomial_sum2(int* A, int lenA, int* B, int lenB, int* result) {
    int max_len = lenA > lenB ? lenA : lenB;
    for (int i = 0; i < max_len; i++) {
        int valA = i < lenA ? A[i] : 0;
        int valB = i < lenB ? B[i] : 0;
        result[i] = valA + valB;
    }
}

// Funzione per calcolare il prodotto dei polinomi usando Karatsuba sbilanciato
int* unbalanced_karatsuba(int n, int* A, int* B) {
    int total_terms = (2 * n) - 1; // Grado del risultato
    int* result = calloc(total_terms, sizeof(int)); // Inizializza risultato a 0

    if (n == 1) { // Caso base: moltiplicazione scalare
        result[0] = A[0] * B[0];
        return result;
    }

    int k = n / 2; // Divisione in base a metà per A0, B0
    int mid = n - k;

    // Divisione dei polinomi in due parti
    int* A0 = A;
    int* A1 = A + mid;
    int* B0 = B;
    int* B1 = B + mid;

    // Calcolo delle dimensioni delle sottoparti
    int size_A1 = n - mid; // A1 ha meno termini rispetto a A0
    int size_B1 = n - mid; // B1 ha meno termini rispetto a B0

    // Somma di A0 + A1 e B0 + B1
    int* A0_plus_A1 = calloc(mid, sizeof(int));
    int* B0_plus_B1 = calloc(mid, sizeof(int));
    polynomial_sum2(A0, mid, A1, size_A1, A0_plus_A1);
    polynomial_sum2(B0, mid, B1, size_B1, B0_plus_B1);

    // Calcoli ricorsivi
    int* P0 = unbalanced_karatsuba(mid, A0, B0);        // P0 = A0 * B0
    int* P2 = unbalanced_karatsuba(size_A1, A1, B1);    // P2 = A1 * B1
    int* P1 = unbalanced_karatsuba(mid, A0_plus_A1, B0_plus_B1); // P1 = (A0 + A1) * (B0 + B1)

    // Calcola P1 - P0 - P2
    for (int i = 0; i < (2 * mid) - 1; i++) {
        P1[i] -= (i < (2 * mid) - 1 ? P0[i] : 0);
        P1[i] -= (i < (2 * size_A1) - 1 ? P2[i] : 0);
    }

    // Combina i risultati
    for (int i = 0; i < (2 * mid) - 1; i++) {
        result[i] += P0[i]; // Termini di P0
    }
    for (int i = 0; i < (2 * mid) - 1; i++) {
        result[i + mid] += P1[i]; // Termini centrali
    }
    for (int i = 0; i < (2 * size_A1) - 1; i++) {
        result[i + (2 * mid)] += P2[i]; // Termini di P2
    }

    // Libera memoria temporanea
    free(A0_plus_A1);
    free(B0_plus_B1);
    free(P0);
    free(P1);
    free(P2);

    return result;
}


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

   int p1[] = {1, 2, 3, 4, 7, 20, 9, 22};
   int p2[] = {4, 3, 2, 1, 10, 5, 3, 10};
   int n = 8;

    int* result =  unbalanced_karatsuba(n, p1, p2);


    // Stampa il risultato
    printf("Risultato: ");
    for (int i = 0; i < (2 * n) - 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}

