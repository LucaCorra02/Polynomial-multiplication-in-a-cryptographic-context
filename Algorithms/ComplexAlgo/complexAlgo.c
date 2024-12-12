#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

void print_coff(double complex coff){
   printf("%.2f + %.2fi", creal(coff), cimag(coff));
}

void print_poly(int n, double complex* p){
    for(int i = 0; i < n; i++){
      print_coff(p[i]);
      printf(" X^%d, ",i);
    }
    printf("\n");
}

double complex* schoolbook_c(int n, double complex* p1, double complex* p2){
    int dim_ris = (2 * n) - 1;
    double complex* ris = calloc(dim_ris, sizeof(double complex));
    if ( n == 1 ) {
      ris[0] += p1[0] * p2[0];
      return ris;
    }

    int max_deg = n - 1;
    double complex mst_p1 = p1[max_deg];
    double complex mst_p2 = p2[max_deg];

    //printf("p2max s%.2f + %.2fi, \n", creal(mst_p2), cimag(mst_p2));
    ris[max_deg * 2] += mst_p1 * mst_p2;
    for (int i = 0; i < max_deg; i++) {
        ris[max_deg + i] += mst_p1 * p2[i]; // Moltiplico il termine di grado massimo di p1 per p2
        ris[max_deg + i] += mst_p2 * p1[i];
    }

    double complex* sub_result = schoolbook_c(max_deg, p1, p2);
    for (int i = 0; i < (dim_ris - 1); i++) { // Combino i risultati
        ris[i] += sub_result[i];
    }

    free(sub_result); // Libera la memoria temporanea usata nella ricorsione.
    return ris;
}

/*
    m = numero di termini di p1 e p2
    n = parti dello split
    k = resto della divisione in i-parti di m
    i = 3. Numero di parti in qui si vuole dividere il polinomio
 */

double complex* sum_poly_complex(int n_p1, int n_p2, double complex* p1, double complex* p2){
  int n_max = (n_p1 > n_p2)? n_p1 : n_p2;
  double complex* ris = calloc(n_max, sizeof(double complex));
  for (int i = 0; i < n_p1; i++) { ris[i] = p1[i]; }
  for (int i = 0; i < n_p2; i++) { ris[i] += p2[i]; }
  return ris;
}

// N = numero di termini del polinomio
int get_split_params(int n){
    n =
}

double complex* split_3_c(int m, double complex* p1, double complex* p2, int n, int k){
    double complex* A0 = p1;
    double complex* A1 = p1 + n;
    double complex* A2 = p1 + (n*2);

    double complex* S1 = sum_poly_complex(n, k, A0, A2);
    double complex* S2 = sum_poly_complex(n, n, S1, A1);

    print_poly(n, S1);
	print_poly(n, S2);
    free(S1);
    free(S2);
    return NULL;
}

void school_main(){
    int n = 3;
    double complex p1[3] = {CMPLX(1.0, 2.0) , CMPLX(3.0, -4.0), CMPLX(5.0, 0.0)};
    double complex p2[3] = {CMPLX(10, 4.0), CMPLX(2.0, -1.0), CMPLX(4.0, 3.0)};

    //printf("%.2f + %.2fi \n", creal(p1[2]), cimag(p1[2]));

    double complex* sum = schoolbook_c(n, p1, p2);
    for (int i = 0; i < (2*n)-1; i++) {
        printf("%.2f + %.2fi, ", creal(sum[i]), cimag(sum[i]));
    }
    free(sum);
    printf("\n");
}


int main(){
    //school_main();

    double complex p1[7] = {
        CMPLX(1.0, 2.0), CMPLX(2.0, 2.0), CMPLX(3.0, 2.0),
        CMPLX(4.0, 2.0), CMPLX(5.0, 2.0), CMPLX(6.0, 2.0),
        CMPLX(7.0, 2.0)
    };
    split_3_c(7, p1, p1, 3, 1);





}