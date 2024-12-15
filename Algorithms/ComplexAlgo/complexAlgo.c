#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

void print_coff(double complex coff){
   printf("%.2f + %.2fi", creal(coff), cimag(coff));
}

void print_poly(int n, double complex* p){
    for(int i = 0; i < n; i++){
      printf("( ");
      print_coff(p[i]);
      printf(" )X^%d, ",i);
    }
    printf("\n");
}

double complex opposite_complex(double complex n){
  return CMPLX(creal(n)*-1, cimag(n)*-1);
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

// ceil, i,n > 0.
int ceil_fast(int n, int i ){
    int ris = n / i;
    return (n % i)? ris+1 : ris;
}

/*
    m = termini polinomio
    i = grado split
    restiuisce le varie possibili taglie di n.
 */
// TODO: Fix n_max formula
int get_split_params(int m, int i){
    int n_min = ceil_fast(m, i);
    int n_max = (2*m) / ((2*i)-1);
    return n_min;
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

double complex* diff_poly_complex(int n_p1, int n_p2, double complex* p1, double complex* p2){
    int n_max = (n_p1 > n_p2)? n_p1 : n_p2;
    double complex* ris = calloc(n_max, sizeof(double complex));
    for (int i = 0; i < n_p1; i++) { ris[i] = p1[i]; }
    for (int i = 0; i < n_p2; i++) { ris[i] = ris[i] - p2[i]; }
    return ris;
}

double complex* diff_poly_complex2(int n_p1, int n_p2, double complex* p1, double complex* p2){
    int n_max = (n_p1 > n_p2)? n_p1 : n_p2;
    double complex* ris = calloc(n_max, sizeof(double complex));
    for (int i = 0; i < n_p1; i++) { ris[i] = p1[i]*-1; }
    for (int i = 0; i < n_p2; i++) { ris[i] -= p2[i]; }
    return ris;
}

double complex* split_3_c(int m, double complex* p1, double complex* p2, int n, int k){
    int dim_ris = (2 * m) - 1;
    double complex* ris = calloc(dim_ris, sizeof(double complex));

    double complex* A0 = p1;
    double complex* A1 = p1 + n;
    double complex* A2 = p1 + (2*n);

    double complex* S1 = sum_poly_complex(n, k, A0, A2);
    double complex* S2 = sum_poly_complex(n, n, S1, A1);
    double complex* S3 = diff_poly_complex(n, n, S1, A1);
    double complex* S4 = diff_poly_complex(n, k, A0, A2);
    double complex* A1w = calloc(n, sizeof(double complex));
    for (int i = 0; i < n; i++) {
      A1w[i] = A1[i] * I;
    }
    double complex* S5 = sum_poly_complex(n, n, S4, A1w);
    free(A1w);

    double complex* B0 = p2;
    double complex* B1 = p2 + n;
    double complex* B2 = p2 + (2*n);

    double complex* S1_p = sum_poly_complex(n, k, B0, B2);
    double complex* S2_p = sum_poly_complex(n, n, S1_p, B1);
    double complex* S3_p = diff_poly_complex(n, n, S1_p, B1);
    double complex* S4_p = diff_poly_complex(n, k, B0, B2);
    double complex* B1w = calloc(n, sizeof(double complex));
    for (int i = 0; i < n; i++) {
        B1w[i] = B1[i] * I;
    }
    double complex* S5_p = sum_poly_complex(n, n, S4_p, B1w);
    free(B1w);

    int dim_pn = (2*n)-1;
    double complex* P0 = schoolbook_c(n, A0, B0);
    double complex* P1 = schoolbook_c(n, S2, S2_p);
    double complex* P2 = schoolbook_c(n, S3, S3_p);
    double complex* P3 = schoolbook_c(n, S5, S5_p);
    double complex* P4 = schoolbook_c(k, A2, B2);

    print_poly(dim_pn, P0);
    print_poly(dim_pn, P1);
    print_poly(dim_pn, P2);
    print_poly(dim_pn, P3);
    print_poly(dim_pn, P4);

    double complex* Q1 = diff_poly_complex(dim_pn, dim_pn, P1, P2);
    double complex* Q2 = sum_poly_complex(dim_pn, dim_pn, P1, P2);
    double complex* Q3 = sum_poly_complex(dim_pn, (2*k)-1, P0, P4);
    double complex* Q4 = diff_poly_complex2(dim_pn, dim_pn, Q2, Q3);
    double complex* Q5 = diff_poly_complex(dim_pn, dim_pn, Q2, Q3);
    double complex* Q6 = diff_poly_complex(dim_pn, dim_pn, Q5, P3);

    double complex* Q6w = calloc(dim_pn, sizeof(double complex));
    for (int i = 0; i < dim_pn; i++) {
        Q6w[i] = Q6[i] * I;
    }
    double complex* Q7 = diff_poly_complex(dim_pn, dim_pn, Q1, Q6w);
    double complex* Q8 = sum_poly_complex(dim_pn, dim_pn, Q1, Q6w);


    printf("Q1: ");
    print_poly(dim_pn, Q1);
    printf("Q2: ");
    print_poly(dim_pn, Q2);
    printf("Q3: ");
    print_poly(dim_pn, Q3);
    printf("Q4: ");
    print_poly(dim_pn, Q4);
    printf("Q5: ");
    print_poly(dim_pn, Q5);
    printf("Q6: ");
    print_poly(dim_pn, Q6);
    printf("Q6w: ");
    print_poly(dim_pn, Q6w);
    free(Q6w);
    printf("Q7: ");
    print_poly(dim_pn, Q7);
    printf("Q8: ");
    print_poly(dim_pn, Q8);

    for (int i = 0; i < dim_pn; i++) {
      ris[i] += P0[i];
      //ris[i + n] += Q7[i];
      //ris [i + 2*n] += Q4[i];
      //ris [i + 2*n+k] += Q8[i];
    }

    free(S1);
    free(S2);
    free(S3);
    free(S4);
    free(S5);
    free(S1_p);
    free(S2_p);
    free(S3_p);
    free(S4_p);
    free(S5_p);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(Q1);
    free(Q2);
    free(Q3);
    free(Q4);
    free(Q5);
    free(Q6);
    free(Q7);
    free(Q8);
    return ris;
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

    /*
    double complex p1[7] = {
        CMPLX(1.0, 2.0), CMPLX(3.0, 4.0), CMPLX(5.0, 6.0),
        CMPLX(2.0, 7.0), CMPLX(8.0, 1.0), CMPLX(9.0, 0.0),
        CMPLX(4.0, 5.0)
    };

    double complex p2[7] = {
        CMPLX(7.0, 6.0), CMPLX(1.0, 0.0), CMPLX(3.0, 8.0),
        CMPLX(4.0, 2.0), CMPLX(5.0, 9.0), CMPLX(0.0, 3.0),
        CMPLX(6.0, 1.0)
    };
     */
    double complex p1[6] = {
        CMPLX(2.0, 1.0), CMPLX(1.0, 3.0), CMPLX(0.0, 2.0),
        CMPLX(3.0, 0.0), CMPLX(2.0, 2.0), CMPLX(1.0, 0.0)
    };

    double complex p2[6] = {
        CMPLX(1.0, 2.0), CMPLX(3.0, 1.0), CMPLX(2.0, 0.0),
        CMPLX(0.0, 3.0), CMPLX(1.0, 1.0), CMPLX(3.0, 2.0)
    };



    int m = 6;
    int i = 3;

    //print_poly(m, p1);
    int n = get_split_params(m, i);
    int k = m-(n*2);
    printf("n = %d, k =%d  \n",n,k);
    double complex* ris = split_3_c(m, p1, p2, n, k);
    print_poly((2*m)-1, ris);
    free(ris);

}