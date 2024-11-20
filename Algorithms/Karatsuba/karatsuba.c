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

void polynomial_sub(int n, int* p1, int* p2, int* ris){ //p1-p2
  for (int i = 0; i < n; i++){
    ris[i] = p1[i] - p2[i];
  }
}

void polynomial_sum(int n, int* p1, int* p2, int* ris){
  for (int i = 0; i < n; i++){
    ris[i] = p1[i] + p2[i];
  }
}

int* karatsuba_recursive(int n, int* p1, int* p2, int* ris){

    if ( n == 1 ) {ris[0] += p1[0]*p2[0]; return ris;} //caso di uscita
    int k = n / 2;
    int* a0 = p1, *a1 = p1 + k;
    int* b0 = p2, *b1 = p2 + k;

    int* P0 = schoolbook_r(k, a0, b0);
    int* P2 = schoolbook_r(k, a1, b1);

    int* sum_a = calloc(k, sizeof(int));
    int* sum_b = calloc(k, sizeof(int));
    polynomial_sum(k, a0, a1, sum_a);
    polynomial_sum(k, b0, b1, sum_b);
    int* P1 = schoolbook_r(k, sum_a, sum_b);
    free(sum_a);
    free(sum_b);

    int dim_sub = (2 * k) - 1;
    int* tmp_sub = calloc(dim_sub,sizeof(int));
    polynomial_sub(dim_sub, P1, P0, tmp_sub);
    polynomial_sub(dim_sub, tmp_sub, P2, tmp_sub);

    printf("P0 : ");
    print_poly(P0,(2*k)-1);
    printf("P1 : ");
    print_poly(P1,(2*k)-1);
    printf("P2 : ");
    print_poly(P2,(2*k)-1);
    printf("SUB : ");
    print_poly(tmp_sub,dim_sub);
    free(P1);
    for (int i = 0; i < n; i++) {
        ris[i] += P0[i];         // Termini di P0
        ris[i + k] += tmp_sub[i]; // Termini di P1 - P0 - P2
        ris[i + n] += P2[i];    // Termini di P2
    }

    free(tmp_sub);
    free(P0);
    free(P2);
    return ris;
}

int* karatsuba_r(int n, int* p1, int* p2) { //n = numero di termini. Suppongo 2n termini,
    if(n % 2 != 0) {return NULL;} //n non nella forma corretta.
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloca e inizializza.
    return karatsuba_recursive(n, p1, p2, ris);
}



int main(int argc, char *argv[]) {




    /*
    int p1[] = {1, 2, 3, 4}; // Polinomio A(X) = 1 + 2x + 3x^2 + 4x^3
    int p2[] = {4, 3, 2, 1}; // Polinomio B(X) = 4 + 3x + 2x^2 + 1x^3
    int n = 4;
    */
    int p1[] = {1, 2, 3, 4, 7, 20};
    int p2[] = {4, 3, 2, 1,-10,5};
    int n = 6;


    int* result = karatsuba_r(n, p1, p2);
    printf("RIS: ");
    print_poly(result,(n*2)-1);

    return 0;
}

