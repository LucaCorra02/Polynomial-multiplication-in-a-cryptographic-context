#include <stdlib.h>
#include "algorithms.h"

/*SCHOOLBOOK IMPLEMENTATION*/

f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2) { //coefficenti solo in f9
    int dim_ris = (2 * n) - 1;
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));
    if (n == 1){
        ris[0] = f9_prod(p1[0],p2[0]);
        return ris;
    }
    int max_deg = n - 1;
    unsigned int mst_p1 = p1[max_deg];
    unsigned int mst_p2 = p2[max_deg];
    ris[max_deg * 2] = f9_sum(ris[max_deg * 2], f9_prod(mst_p1,mst_p2));

    for (int i = 0; i < max_deg; i++) {
        ris[max_deg + i] = f9_sum(ris[max_deg + i], f9_prod(mst_p1, p2[i]));
        ris[max_deg + i] = f9_sum(ris[max_deg + i], f9_prod(mst_p2, p1[i]));
    }
    //print_vector(ris,dim_ris);
    f9_element* sub_result = schoolbook_f9(n - 1, p1, p2);
    for (int i = 0; i < (dim_ris - 1); i++) {
        ris[i] = f9_sum(ris[i],sub_result[i]);
    }
    free(sub_result);
    return ris;
}

int* schoolbook_f3(int n, int* p1, int* p2) {
    int dim_ris = (2 * n) - 1;
    int* ris = calloc(dim_ris, sizeof(int));
    if (n == 1) { ris[0] = f3_prod(p1[0], p2[0]); return ris; }
    int max_deg = n - 1;
    unsigned int mst_p1 = p1[max_deg];
    unsigned int mst_p2 = p2[max_deg];
    ris[max_deg * 2] = f3_sum(ris[max_deg * 2], f3_prod(mst_p1,mst_p2));

    for (int i = 0; i < max_deg; i++) {
        ris[max_deg + i] = f3_sum(ris[max_deg + i], f3_prod(mst_p1, p2[i]));
        ris[max_deg + i] = f3_sum(ris[max_deg + i], f3_prod(mst_p2, p1[i]));
    }

    int* sub_result = schoolbook_f3(n - 1, p1, p2);
    for (int i = 0; i < (dim_ris - 1); i++) {
        ris[i] = f3_sum(ris[i],sub_result[i]);
    }

    free(sub_result);
    return ris;
}

/* KARATSUBA Implementation */

void polynomial_sum_f3(int* p1, int len_p1, int* p2, int len_p2, int* ris) { // Somma per polinomi sbilanciati
    for (int i = 0; i < len_p1; i++) ris[i] = f3_sum(int_to_f3(ris[i]), int_to_f3(p1[i]));
    for (int i = 0; i < len_p2; i++) ris[i] = f3_sum(int_to_f3(ris[i]), int_to_f3(p2[i]));
}

int* unbalanced_karatsuba_f3(int n, int* p1, int* p2) {
    int* result = calloc((2 * n) - 1, sizeof(int));
    if (n == 1) { result[0] = f3_prod(int_to_f3(p1[0]), int_to_f3(p2[0])); return result; }

    int k = n / 2;
    int mid = n - k; // Resto divisione
    int* a0 = p1;
    int* a1 = p1 + mid; // a1 ha meno terimi rispetto ad a0
    int* b0 = p2;
    int* b1 = p2 + mid;
    int size_a1 = n - mid, size_b1 = n - mid;

    int* a0a1 = calloc(mid, sizeof(int));
    int* b0b1 = calloc(mid, sizeof(int));
    polynomial_sum_f3(a0, mid, a1, size_a1, a0a1);
    polynomial_sum_f3(b0, mid, b1, size_b1, b0b1);

    int *P0, *P1, *P2;
    #pragma omp parallel sections
    {
        #pragma omp section
            P0 = unbalanced_karatsuba_f3(mid, a0, b0); // P0 = A0 * B0
        #pragma omp section
            P2 = unbalanced_karatsuba_f3(size_a1, a1, b1); // P2 = A1 * B1
        #pragma omp section
            P1 = unbalanced_karatsuba_f3(mid, a0a1, b0b1); // P1 = (A0 + A1) * (B0 + B1)
    }

    for (int i = 0; i < (2 * mid ) - 1; i++){ P1[i] = f3_sum(int_to_f3(P1[i]), swap_bits(int_to_f3(P0[i]))); } // P1 = P1 - P0
    for (int i = 0; i < (2 * size_a1) - 1; i++) { P1[i] = f3_sum(int_to_f3(P1[i]), swap_bits(int_to_f3(P2[i])));  } // P1 = (P1 - P0) - P0

    //Combini i risultati
    for (int i = 0; i < (2 * mid ) - 1; i++) {
        result[i] = f3_sum(int_to_f3(result[i]), int_to_f3(P0[i])); // Termini da 0 a mid-1
        result[i + mid] = f3_sum(int_to_f3(result[i + mid]), int_to_f3(P1[i])); // Terimini da mid a (2*mid)-1
    }
    for (int i = 0; i < (2 * size_a1) - 1; i++) {
        result[i + (2 * mid)] = f3_sum(int_to_f3(result[i + (2 * mid)]), int_to_f3(P2[i])); // Termini da (2*mid) a n-1
    }

    free(a0a1);
    free(b0b1);
    free(P0);
    free(P1);
    free(P2);
    return result;
}

void polynomial_sum_f9(f9_element* p1, int len_p1, f9_element* p2, int len_p2, f9_element* ris) { // Somma per polinomi sbilanciati
    for (int i = 0; i < len_p1; i++) ris[i] = f9_sum(ris[i], p1[i]);
    for (int i = 0; i < len_p2; i++) ris[i] = f9_sum(ris[i], p2[i]);
}

f9_element* unbalanced_karatsuba_f9(int n, f9_element* p1, f9_element* p2) {
    f9_element* result = calloc((2 * n) - 1, sizeof(f9_element));
    if (n == 1) { result[0] = f9_prod(p1[0], p2[0]); return result; }

    int k = n / 2;
    int mid = n - k; // Resto divisione
    f9_element* a0 = p1;
    f9_element* a1 = p1 + mid; // a1 ha meno terimi rispetto ad a0
    f9_element* b0 = p2;
    f9_element* b1 = p2 + mid;
    int size_a1 = n - mid, size_b1 = n - mid;

    f9_element* a0a1 = calloc(mid, sizeof(f9_element));
    f9_element* b0b1 = calloc(mid, sizeof(f9_element));
    polynomial_sum_f9(a0, mid, a1, size_a1, a0a1);
    polynomial_sum_f9(b0, mid, b1, size_b1, b0b1);

    f9_element* P0 = unbalanced_karatsuba_f9(mid, a0, b0); // P0 = A0 * B0
    f9_element* P2 = unbalanced_karatsuba_f9(size_a1, a1, b1); // P2 = A1 * B1
    f9_element* P1 = unbalanced_karatsuba_f9(mid, a0a1, b0b1); // P1 = (A0 + A1) * (B0 + B1)

    for (int i = 0; i < (2 * mid ) - 1; i++){ P1[i] = f9_sum(P1[i], f9_neg(P0[i])); } // P1 = P1 - P0
    for (int i = 0; i < (2 * size_a1) - 1; i++) { P1[i] = f9_sum(P1[i], f9_neg(P2[i])); } // P1 = (P1 - P0) - P0

    //Combini i risultati
    for (int i = 0; i < (2 * mid ) - 1; i++) {
        result[i] = f9_sum(result[i], P0[i]); // Termini da 0 a mid-1
        result[i + mid] = f9_sum(result[i + mid], P1[i]); // Terimini da mid a (2*mid)-1
    }
    for (int i = 0; i < (2 * size_a1) - 1; i++) {
        result[i + (2 * mid)] = f9_sum(result[i + (2 * mid)], P2[i]); // Termini da (2*mid) a n-1
    }

    free(a0a1);
    free(b0b1);
    free(P0);
    free(P1);
    free(P2);
    return result;
}

/* 3_SPLIT_V1 Implementation */

f9_element* split_3_f9(int m, f9_element* p1, f9_element* p2){
    if (m < 6){
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n, 3);

    f9_element* A0 = p1; //dim n
    f9_element* A1 = p1 + n; //dim n
    f9_element* A2 = p1 + 2*n; // dim k, tot m = 2*n+k

    f9_element* B0 = p2;
    f9_element* B1 = p2 + n;
    f9_element* B2 = p2 + 2*n;

    int op_part1 = (10);
    int op_part2 = (8);
    f9_element* op_pointer = allocate_mem(op_part1, n, op_part2, (2*n-1));

    f9_element* S1 = op_pointer;
    sum_poly(n, k, A0, A2, S1);    // A0 + A2. Dim n,k = n
    f9_element* S2 = op_pointer + n;
    sum_poly(n, n, S1, A1, S2);    // S1 + A1. Dim n,n = n
    f9_element* S3 = op_pointer + 2*n;
    diff_poly(n, n, S1, A1, S3);   // S2 - A1 Dim n,n = n
    f9_element* S4 = op_pointer + 3*n;
    diff_poly(n, k, A0, A2, S4);   // A0 - A2 Dim n,k = n
    f9_element* S5 = op_pointer + 4*n;
    sum_poly_img(n , n, S4, A1, S5);// S4 + A1w Dim n,n = n

    f9_element* S1_b = S5 + n ;
    sum_poly(n, k, B0, B2, S1_b);   // B0 + B2. Dim n,k = n
    f9_element* S2_b = S1_b + n;
    sum_poly(n, n, S1_b, B1, S2_b); // S1_b + B1. Dim n,n = n
    f9_element* S3_b = S1_b + 2*n;
    diff_poly(n, n, S1_b, B1, S3_b); // S2_b - B1 Dim n,n = n
    f9_element* S4_b = S1_b + 3*n;
    diff_poly(n, k, B0, B2, S4_b);  // B0 - B2 Dim n,k = n
    f9_element* S5_b = S1_b + 4*n;
    sum_poly_img(n, n, S4_b, B1, S5_b); // S4_b + B1w Dim n,n = n


    f9_element *P0, *P1, *P2, *P3, *P4;
    #pragma omp parallel sections
    {
        #pragma omp section
        P0 = split_3_f9(n, A0, B0);

        #pragma omp section
        P1 = split_3_f9(n, S2, S2_b);

        #pragma omp section
        P2 = split_3_f9(n, S3, S3_b);

        #pragma omp section
        P3 = split_3_f9(n, S5, S5_b);

        #pragma omp section
        P4 = split_3_f9(k, A2, B2);
    }

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);
    f9_element* Q1 = S5_b + n;
    diff_poly(dim_subproduct, dim_subproduct, P1, P2, Q1); //P1 - P2
    f9_element* Q2 = Q1 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, P1, P2, Q2);  //P1 + P2
    f9_element* Q3 = Q1 + 2*dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct_rem, P0, P4, Q3); // P0 + P4
    f9_element* Q4 = Q1 + 3*dim_subproduct;
    diff_poly_double(dim_subproduct, dim_subproduct, Q2, Q3, Q4); // -Q2 - Q3
    f9_element* Q5 = Q1 + 4*dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, Q2, Q3, Q5); // Q2 - Q3
    f9_element* Q6 = Q1 + 5*dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, Q5, P3, Q6); // Q5 - P3
    f9_element* Q7 = Q1 + 6*dim_subproduct;
    sum_poly_img_neg(dim_subproduct, dim_subproduct, Q1, Q6, Q7); // Q1 - wQ6
    f9_element* Q8 = Q1 + 7*dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q1, Q6, Q8); //Q1 + wQ6

    int dim_ris = (2*m-1);
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i] = f9_sum(ris[i], P0[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+n] = f9_sum(ris[i+n], Q7[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+2*n] = f9_sum(ris[i+2*n], Q4[i]);
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
    	ris[i+3*n] = f9_sum(ris[i+3*n], Q8[i]);
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
    	ris[i+4*n] = f9_sum(ris[i+4*n], P4[i]);
    }

    free(op_pointer);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    return ris;
}

int* split_3_f3(int m, int* p1, int* p2){
	if (m < 6){
        return schoolbook_f3(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n, 3);

   	int* A0 = p1; //dim n
    int* A1 = p1 + n; //dim n
    int* A2 = p1 + 2*n; // dim k, tot m = 2*n+k

    int* B0 = p2;
    int* B1 = p2 + n;
    int* B2 = p2 + 2*n;

    int op_part1 = (8);
    int op_part2 = (5);
    int* op_pointer = allocate_mem_f3(op_part1, n, op_part2, (2*n-1));
    f9_element* op_pointer_f9 = calloc((n)*2, sizeof(f9_element));

    int* S1 = op_pointer;
    sum_poly_f3(n, k, A0, A2, S1); // S1 = A0 + A2
    int* S2 = S1 + n;
    sum_poly_f3(n, n, S1, A1, S2); // S2 = S1 + A1
    int* S3 = S2 + n;
    diff_poly_f3(n, n, S1, A1, S3); // S3 = S1 - A1
    int* S4 = S3 + n;
    diff_poly_f3(n, k, A0, A2, S4); // S4 = A0 - A2
    f9_element* S5 = op_pointer_f9;
    sum_poly_img_f3(n, n, S4, A1, S5); // S5 = S4 + A1w

    int* S1_b = S4 + n ;
    sum_poly_f3(n, k, B0, B2, S1_b); // S1_b = B0 + B2
    int* S2_b = S1_b + n;
    sum_poly_f3(n, n, S1_b, B1, S2_b); // S2_b = S1_b + B1
    int* S3_b = S2_b + n;
    diff_poly_f3(n, n, S1_b, B1, S3_b); // S3_b = S1_b - B1
    int* S4_b = S3_b + n;
    diff_poly_f3(n, k, B0, B2, S4_b); // S4_b = B0 - B2
    f9_element* S5_b = S5 + n;
    sum_poly_img_f3(n, n, S4_b, B1, S5_b); // S5_b = S4_b + B1w

    int *P0, *P1, *P2, *P4;
    f9_element *P3;
    #pragma omp parallel sections
    {
       #pragma omp section
       P0 = split_3_f3(n, A0, B0);
       #pragma omp section
       P1 = split_3_f3(n, S2, S2_b);
       #pragma omp section
       P2 = split_3_f3(n, S3, S3_b);
       #pragma omp section
       P3 = split_3_f9(n, S5, S5_b);
       #pragma omp section
       P4 = split_3_f3(k, A2, B2);
    }

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    int* Q1 = S4_b + n;
    diff_poly_f3(dim_subproduct, dim_subproduct, P1, P2, Q1); // Q1 = P1 - P2
    int* Q2 = Q1 + dim_subproduct;
    diff_poly_img_f3(dim_subproduct, dim_subproduct, Q1, P3, Q2); // Q2 = Q1 - P3,1
    int* Q3 = Q2 + dim_subproduct;
    sum_poly_imag_f3(dim_subproduct, dim_subproduct, Q1, P3, Q3); // Q3 = Q1 + P3,1
    int* Q4 = Q3 + dim_subproduct;
    diff_poly_real_f3(dim_subproduct, dim_subproduct, P0, P3, Q4); // Q4 = P0 - P3,0
    int* Q5 = Q4 + dim_subproduct;
    sum_poly_f3(dim_subproduct, dim_subproduct_rem, Q4, P4, Q5); // Q5 = Q4 + P4

    int dim_ris = (2*m-1);
    int* ris = calloc(dim_ris, sizeof(int));

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i] = f3_sum(ris[i], P0[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+n] = f3_sum(ris[i+n], Q2[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+2*n] = f3_sum(ris[i+2*n], Q5[i]);
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
    	ris[i+3*n] = f3_sum(ris[i+3*n], Q3[i]);
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
    	ris[i+4*n] = f3_sum(ris[i+4*n], P4[i]);
    }

    free(op_pointer);
    free(op_pointer_f9);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    return ris;
}


/* 3_SPLIT_V2 Implementation */

f9_element* split_3_v2_f9(int m, f9_element* p1, f9_element* p2){
    if (m < 6){
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n, 3);

    f9_element* A0 = p1; //dim n
    f9_element* A1 = p1 + n; //dim n
    f9_element* A2 = p1 + 2*n; // dim k, tot m = 2*n+k

    f9_element* B0 = p2;
    f9_element* B1 = p2 + n;
    f9_element* B2 = p2 + 2*n;

    int op_part1 = (10);
    int op_part2 = (8);
    f9_element* op_pointer = allocate_mem(op_part1, n, op_part2, (2*n-1));

    f9_element* S1 = op_pointer;
    diff_poly(n, k, A0, A2, S1); // S1 = A0 - A2
    f9_element* S2 = S1 + n;
    sum_poly_img(n, n, S1, A1, S2); // S2 = S1 + wA1
    f9_element* S3 = S2 + n;
    sum_poly_img_neg(n, n, S1, A1, S3); // S3 = S1 - wA1
    f9_element* S4 = S3 + n;
    sum_poly(n, k, A0, A2, S4); // S4 = A0 + A2
    f9_element* S5 = S4 + n;
    sum_poly(n, n, S4, A1, S5); // S5 = S4 + A1

    f9_element* S1_b = S5 + n;
    diff_poly(n, k, B0, B2, S1_b); // S1_b = B0 - B2
    f9_element* S2_b = S1_b + n;
    sum_poly_img(n, n, S1_b, B1, S2_b); // S2_b = S1_b + wB1
    f9_element* S3_b = S2_b + n;
    sum_poly_img_neg(n, n, S1_b, B1, S3_b); // S3_b = S1_b - wB1
    f9_element* S4_b = S3_b + n;
    sum_poly(n, k, B0, B2, S4_b); // S4_b = B0 + B2
    f9_element* S5_b = S4_b + n;
    sum_poly(n, n, S4_b, B1, S5_b); // S5_b = S4_b + B1

    f9_element *P0, *P1, *P2, *P3, *P4;
    #pragma omp parallel sections
    {
        #pragma omp section
        P0 = split_3_v2_f9(n, A0, B0);

        #pragma omp section
        P1 = split_3_v2_f9(n, S5, S5_b);

        #pragma omp section
        P2 = split_3_v2_f9(n, S2, S2_b);

        #pragma omp section
        P3 = split_3_v2_f9(n, S3, S3_b);

        #pragma omp section
        P4 = split_3_v2_f9(k, A2, B2);
    }

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    f9_element* Q1 = S5_b + n;
    sum_poly(dim_subproduct, dim_subproduct, P2, P3, Q1); // Q1 = P2 + P3
    f9_element* Q2 = Q1 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct_rem, P0, P4, Q2); // Q2 = P0 + P4
    f9_element* Q3 = Q2 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, Q1, Q2, Q3); // Q3 = Q1 + Q2
    f9_element* Q4 = Q3 + dim_subproduct;
    diff_poly_double(dim_subproduct, dim_subproduct, Q2, P1, Q4); // Q4 = - Q2 - P1
    f9_element* Q5 = Q4 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, Q4, Q1, Q5);
    f9_element* Q6 = Q5 + dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, P2, P3, Q6);
    f9_element* Q7 = Q6 + dim_subproduct;
    sum_poly_img_neg(dim_subproduct, dim_subproduct, Q5, Q6, Q7);
    f9_element* Q8 = Q7 + dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q5, Q6, Q8);

    int dim_ris = (2*m-1);
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));

    for(int i = 0; i < dim_subproduct ; i++){
        ris[i] = f9_sum(ris[i], P0[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
        ris[i+n] = f9_sum(ris[i+n], Q7[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
        ris[i+2*n] = f9_sum(ris[i+2*n], Q3[i]);
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+3*n] = f9_sum(ris[i+3*n], Q8[i]);
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
        ris[i+4*n] = f9_sum(ris[i+4*n], P4[i]);
    }

    free(op_pointer);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    return ris;
}


int* split_3_v2_f3(int m, int* p1, int* p2){
	if (m < 6){
        return schoolbook_f3(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n, 3);

   	int* A0 = p1; //dim n
    int* A1 = p1 + n; //dim n
    int* A2 = p1 + 2*n; // dim k, tot m = 2*n+k

    int* B0 = p2;
    int* B1 = p2 + n;
    int* B2 = p2 + 2*n;

    int op_part1 = (6);
    int op_part2 = (6);
    int* op_pointer = allocate_mem_f3(op_part1, n, op_part2, (2*n-1));
    f9_element* op_pointer_f9 = calloc((n) * 2, sizeof(f9_element));

    int* S1 = op_pointer;
    diff_poly_f3(n, k, A0, A2, S1); // S1 = A0 - A2
    f9_element* S2 = op_pointer_f9;
    sum_poly_img_f3(n, n, S1, A1, S2); // S2 = S1 + wA1
	int* S3 = S1 + n;
    sum_poly_f3(n, k, A0, A2, S3); // S3 = A0 + A2
    int* S4 = S3 + n;
    sum_poly_f3(n, n, S3, A1, S4); // S4 = S3 + A1

    int* S1_b = S4 + n;
    diff_poly_f3(n, k, B0, B2, S1_b); // S1_b = B0 - B2
    f9_element* S2_b = S2 + n;
    sum_poly_img_f3(n, n, S1_b, B1, S2_b); // S2_b = S1_b + wB1
    int* S3_b = S1_b + n;
    sum_poly_f3(n, k, B0, B2, S3_b); // S3_b = B0 + B2
    int* S4_b = S3_b + n;
    sum_poly_f3(n, n, S3_b, B1, S4_b); // S4_b = S3_b + B1

	int *P0, *P1, *P4;
    f9_element *P2;

    #pragma omp parallel sections
    {
        #pragma omp section
        P0 = split_3_v2_f3(n, A0, B0); // P0 = A0*B0

        #pragma omp section
        P1 = split_3_v2_f3(n, S4, S4_b); // P1 = S4 * S4_b

        #pragma omp section
        P2 = split_3_v2_f9(n, S2, S2_b); //P2 = S2 * S2_b Su F9

        #pragma omp section
        P4 = split_3_v2_f3(k, A2, B2); //P4 = A2 * B2
    }

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    int* Q1 = S4_b + n;
    sum_poly_f3(dim_subproduct, dim_subproduct_rem, P0, P4, Q1); // Q1 = P0 + P4
    int* Q2 = Q1 + dim_subproduct;
    diff_poly_real_f3(dim_subproduct, dim_subproduct, Q1, P2, Q2); // Q2 = Q1 - P2_real_part
    int* Q3 = Q2 + dim_subproduct;
    sum_poly_real_f3(dim_subproduct, dim_subproduct, Q1, P2, Q3); //Q3 = Q1 + P2_real_part
    int* Q4 = Q3 + dim_subproduct;
    sum_poly_f3(dim_subproduct, dim_subproduct, Q3, P1, Q4); // Q4 = Q3 + P1
    int* Q5 = Q4 + dim_subproduct;
    diff_double_poly_imag_f3(dim_subproduct, dim_subproduct, Q4, P2, Q5); // Q5 = - Q4 - P2_imag_part
    int* Q6 = Q5 + dim_subproduct;
    diff_single_poly_imag_f3(dim_subproduct, dim_subproduct, Q4, P2, Q6); // Q6 = - Q4 + P2_imag_part

    int dim_ris = (2*m-1);
    int* ris = calloc(dim_ris, sizeof(int));

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i] = f3_sum(ris[i], P0[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+n] = f3_sum(ris[i+n], Q5[i]);
    }
    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+2*n] = f3_sum(ris[i+2*n], Q2[i]);
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
    	ris[i+3*n] = f3_sum(ris[i+3*n], Q6[i]);
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
    	ris[i+4*n] = f3_sum(ris[i+4*n], P4[i]);
    }

    free(op_pointer);
    free(op_pointer_f9);
    free(P0);
    free(P1);
    free(P2);
    free(P4);
    return ris;
}

/* 4_SPLIT_V2 IMPLEMENTATION */

f9_element* split_4_f9(int m, f9_element* p1, f9_element* p2){
    if (m < 18){
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 4);
    int k = get_split_k_param(m, n, 4);

    f9_element* A0 = p1;
    f9_element* A1 = p1 + n;
    f9_element* A2 = p1 + 2 * n;
    f9_element* A3 = p1 + 3 * n;

    f9_element* B0 = p2;
    f9_element* B1 = p2 + n;
    f9_element* B2 = p2 + 2 * n;
    f9_element* B3 = p2 + 3 * n;

    int op_part1 = (20);
    int op_part2 = (17);
    f9_element* op_pointer = allocate_mem(op_part1, n, op_part2, (2*n-1));

    f9_element* S1 = op_pointer;
    sum_poly(n, k, A1, A3, S1); // S1 = A1 + A3
    f9_element* S2 = S1 + n;
    sum_poly(n, n, A2, S1, S2); // S2 = A2 + S1
    f9_element* S3 = S2 + n;
    sum_poly(n, n, A0, S2, S3); // S3 = A0 + S2
    f9_element* S4 = S3 + n;
    sum_poly(n, n, A0, S1, S4); // S4 = A0 + S1
    f9_element* S5 = S4 + n;
    sum_poly(n, n, A1, S2, S5); //S5 = A1 + S2
    f9_element* S6 = S5 + n;
    sum_poly_img_neg(n, n, S4, S5, S6); // S6 = S4 -wS5
    f9_element* S7 = S6 + n;
    sum_poly_img(n, n, S4, S5, S7); // S7 = S4 + wS5
    f9_element* S8 = S7 + n;
    sum_poly_img(n, n, A2, S6, S8); //S8 = A2 + wS6
    f9_element* S9 = S8 + n;
    neg_sum_poly_img(n, n, A0, S8, S9); // S9 = -A0 + wS8
    f9_element* S10 = S9 + n;
    sum_poly_img_neg(n, n, S1, S8, S10); //S10 = S1 - wS8

    f9_element* S1_b = S10 + n;
    sum_poly(n, k, B1, B3, S1_b); // S1_b = B1 + B3
    f9_element* S2_b = S1_b + n;
    sum_poly(n, n, B2, S1_b, S2_b); // S2_b = B2 + S1_b
    f9_element* S3_b = S2_b + n;
    sum_poly(n, n, B0, S2_b, S3_b); // S3_b = B0 + S2_b
    f9_element* S4_b = S3_b + n;
    sum_poly(n, n, B0, S1_b, S4_b); // S4_b = B0 + S1_b
    f9_element* S5_b = S4_b + n;
    sum_poly(n, n, B1, S2_b, S5_b); //S5_b = B1 + S2_b
    f9_element* S6_b = S5_b + n;
    sum_poly_img_neg(n, n, S4_b, S5_b, S6_b); // S6_b = S4_b -wS5_b
    f9_element* S7_b = S6_b + n;
    sum_poly_img(n, n, S4_b, S5_b, S7_b); // S7_b = S4_b + wS5_b
    f9_element* S8_b = S7_b + n;
    sum_poly_img(n, n, B2, S6_b, S8_b); //S8_b = B2 + wS6_b
    f9_element* S9_b = S8_b + n;
    neg_sum_poly_img(n, n, B0, S8_b, S9_b); // S9_b = -B0 + wS8_b
    f9_element* S10_b = S9_b + n;
    sum_poly_img_neg(n, n, S1_b, S8_b, S10_b); //S10_b = S1_b - wS8_b

    f9_element *P0, *P1, *P2, *P3, *P4, *P5, *P6;
    P0 = split_4_f9(n, A0, B0);
    P1 = split_4_f9(n, S3, S3_b);
    P2 = split_4_f9(n, S6, S6_b);
    P3 = split_4_f9(n, S7, S7_b);
    P4 = split_4_f9(n, S9, S9_b);
    P5 = split_4_f9(n, S10, S10_b);
    P6 = split_4_f9(k, A3, B3);

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    f9_element* Q1 = S10_b + n;
    sum_poly(dim_subproduct, dim_subproduct, P2, P4, Q1); // Q1 = P2 + P4
    f9_element* Q2 = Q1 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, P3, P5, Q2); //Q2 = P3 + P5
    f9_element* Q3 = Q2 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, Q1, Q2, Q3); //Q3 = Q1 + Q2
    f9_element* Q4 = Q3 + dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, P0, Q3, Q4); //Q4 = P0 - Q3
    f9_element* Q5 = Q4 + dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, Q1, Q2, Q5); // Q5 = Q1 - Q2
    f9_element* Q6 = Q5 + dim_subproduct;
    sum_poly_img(dim_subproduct_rem, dim_subproduct, P6, Q5, Q6); // Q6 = P6 + wQ5
    f9_element* Q7 = Q6 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, P0, P1, Q7); // Q7 = P0 + P1
    f9_element* Q8 = Q7 + dim_subproduct;
    sum_poly(dim_subproduct_rem, dim_subproduct, P6, Q7, Q8); //Q8 = P6 + Q7
    f9_element* Q9 = Q8 + dim_subproduct;
    diff_poly(dim_subproduct, dim_subproduct, P2, P3, Q9); //Q9 = P2 - P3
    f9_element* Q10 = Q9 + dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q3, Q9, Q10); //Q10 = Q3 + wQ9
    f9_element* Q11 = Q10 + dim_subproduct;
    diff_poly_double(dim_subproduct, dim_subproduct, Q8, Q10, Q11); //Q11 = -Q8 - Q10
    f9_element* Q12 = Q11 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, P2, P3, Q12); //Q12 = P2 + P3
    f9_element* Q13 = Q12 + dim_subproduct;
    sum_poly_img_neg(dim_subproduct, dim_subproduct, Q5, Q10, Q13); //Q13 = Q5 -wQ10
    f9_element* Q14 = Q13 + dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q12, Q13, Q14); //Q14 = Q12 + wQ13
    f9_element* Q15 = Q14 + dim_subproduct;
    sum_poly(dim_subproduct, dim_subproduct, P4, P5, Q15); //Q15 = P4 + P5
    f9_element* Q16 = Q15 + dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q5, Q8, Q16); //Q16 = Q5 + wQ8
    f9_element* Q17 = Q16 + dim_subproduct;
    sum_poly_img(dim_subproduct, dim_subproduct, Q15, Q16, Q17); //Q17 = Q15 + wQ16

    int dim_ris = (2*m-1);
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));

    for(int i = 0; i < dim_subproduct ; i++){
        ris[i] = f9_sum(ris[i], P0[i]); //R0
    }
    for(int i = 0; i < dim_subproduct ; i++){
        ris[i+n] = f9_sum(ris[i+n], Q11[i]); //R1
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris ; i++){
        ris[i+2*n] = f9_sum(ris[i+2*n], Q6[i]); //R2
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+3*n] = f9_sum(ris[i+3*n], Q14[i]); //R3
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+4*n] = f9_sum(ris[i+4*n], Q4[i]); //R4
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+5*n] = f9_sum(ris[i+5*n], Q17[i]); //R5
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
        ris[i+6*n] = f9_sum(ris[i+6*n], P6[i]);
    }

    free(op_pointer);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
	free(P5);
    free(P6);
    return ris;
}

int* split_4_f3(int m, int* p1, int* p2){
    if (m < 18){
        return schoolbook_f3(m, p1, p2);
    }
    int n = get_split_n_param(m, 4);
    int k = get_split_k_param(m, n, 4);

    int* A0 = p1;
    int* A1 = p1 + n;
    int* A2 = p1 + 2 * n;
    int* A3 = p1 + 3 * n;

    int* B0 = p2;
    int* B1 = p2 + n;
    int* B2 = p2 + 2 * n;
    int* B3 = p2 + 3 * n;

    int op_part1 = (14);
    int op_part2 = (11);
    int* op_pointer = allocate_mem_f3(op_part1, n, op_part2, (2*n-1));
    f9_element* op_pointer_f9 = calloc((n) * 8, sizeof(f9_element));

    int* S1 = op_pointer;
    sum_poly_f3(n, k, A1, A3, S1); // S1 = A1 + A3
    int* S2 = S1 + n;
    sum_poly_f3(n, n, S1, A0, S2); // S2 = S1 + A0
    int* S3 = S2 + n;
    diff_poly_f3(n, n, A0, S1, S3); // S3 = A0 - S1
    int* S4 = S3 + n;
    sum_poly_f3(n, n, S2, A2, S4); // S4 = S2 + A2
    int* S5 = S4 + n;
    diff_poly_double_f3(n, n, A2, S1, S5); // S5 = -A2 -S1
    int* S6 = S5 + n;
    diff_poly_f3(n, n, S5, A1, S6); // S6 = S5 - A1
    int* S7 = S6 + n;
    diff_poly_f3(n, k, S5, A3, S7); //S7 = S5 - A3
    f9_element* S8 = op_pointer_f9;
    sum_poly_img_f3(n, n, S2, S6, S8); //S8 = S2 + wS6
    f9_element* S9 = S8 + n;
    sum_poly_neg_img_f3(n, n, S2, S6, S9); //S9 = S2 -wS6
    f9_element* S10 = S9 + n;
    sum_poly_img_f3(n, n, S3, S7, S10); //S10 = S3 + wS7
    f9_element* S11 = S10 + n;
    sum_poly_neg_img_f3(n, n, S3, S7, S11); //S11 = S3 - wS7

    int* S1_b = S7 + n;
    sum_poly_f3(n, k, B1, B3, S1_b); // S1_b = B1 + B3
    int* S2_b = S1_b + n;
    sum_poly_f3(n, n, S1_b, B0, S2_b); // S2_b = S1_b + B0
    int* S3_b = S2_b + n;
    diff_poly_f3(n, n, B0, S1_b, S3_b); // S3_b = B0 - S1_b
    int* S4_b = S3_b + n;
    sum_poly_f3(n, n, S2_b, B2, S4_b); // S4_b = S2_b + B2
    int* S5_b = S4_b + n;
    diff_poly_double_f3(n, n, B2, S1_b, S5_b); // S5_b = -B2 -S1_b
    int* S6_b = S5_b + n;
    diff_poly_f3(n, n, S5_b, B1, S6_b); // S6_b = S5_b - B1
    int* S7_b = S6_b + n;
    diff_poly_f3(n, k, S5_b, B3, S7_b); //S7_b = S5_b - B3
    f9_element* S8_b = S11 + n;
    sum_poly_img_f3(n, n, S2_b, S6_b, S8_b); //S8_b = S2_b + wS6_b
    f9_element* S9_b = S8_b + n;
    sum_poly_neg_img_f3(n, n, S2_b, S6_b, S9_b); //S9_b = S2_b -wS6_b
    f9_element* S10_b = S9_b + n;
    sum_poly_img_f3(n, n, S3_b, S7_b, S10_b); //S10_b = S3_b + wS7_b
    f9_element* S11_b = S10_b + n;
    sum_poly_neg_img_f3(n, n, S3_b, S7_b, S11_b); //S11_b = S3_b - wS7_b

    int *P0, *P1, *P6;
    f9_element *P2, *P3, *P4, *P5;
    P0 = split_4_f3(n, A0, B0);
    P1 = split_4_f3(n, S4, S4_b);
    P2 = split_4_f9(n, S8, S8_b);
    P3 = split_4_f9(n, S9, S9_b);
    P4 = split_4_f9(n, S10, S10_b);
    P5 = split_4_f9(n, S11, S11_b);
    P6 = split_4_f3(k, A3, B3);

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    int* Q1 = S7_b + n;
    sum_poly_double_real_f3(dim_subproduct, dim_subproduct, P2, P4, Q1); // Q1 = P2,0 + P4,0
    int* Q2 = Q1 + dim_subproduct;
    sum_poly_f3(dim_subproduct, dim_subproduct, P0, Q1, Q2); // Q2 = P0 + Q1
    int* Q3 = Q2 + dim_subproduct;
    sum_poly_imag_f3(dim_subproduct_rem, dim_subproduct, P6, P2, Q3); //Q3 = P6 + P2,1
    int* Q4 = Q3 + dim_subproduct;
    sum_poly_imag_f3(dim_subproduct, dim_subproduct, Q3, P4, Q4); //Q4 = Q3 + P4,1
    int* Q5 = Q4 + dim_subproduct;
    sum_poly_f3(dim_subproduct, dim_subproduct, Q2, P1, Q5); //Q5 = Q2 + P1
    int* Q6 = Q5 + dim_subproduct;
    sum_poly_real_img_f3(dim_subproduct, dim_subproduct, P2, P4, Q6); //Q6 = P2,0 + P4,1
    int* Q7 = Q6 + dim_subproduct;
    diff_single_poly_imag_f3(dim_subproduct, dim_subproduct, Q6, P2, Q7); //Q7 = -Q6 + P2,1
    int* Q8 = Q7 + dim_subproduct;
    diff_double_poly_real_f3(dim_subproduct, dim_subproduct, Q7, P4, Q8); //Q8 = -Q7 -P4,0
    int* Q9 = Q8 + dim_subproduct;
    sum_poly_f3(dim_subproduct, dim_subproduct, Q5, Q3, Q9); //Q9 = Q5 + Q3
    int* Q10 = Q9 + dim_subproduct;
    diff_poly_double_f3(dim_subproduct, dim_subproduct, Q9, Q1, Q10); //Q10 = -Q9 - Q1
    int* Q11 = Q10 + dim_subproduct;
    diff_poly_double_f3(dim_subproduct, dim_subproduct, Q7, Q9, Q11); //Q11 = -Q7 - Q9

    int dim_ris = (2*m-1);
    int* ris = calloc(dim_ris, sizeof(int));

    for(int i = 0; i < dim_subproduct ; i++){
        ris[i] = f3_sum(ris[i], P0[i]); //R0
    }
    for(int i = 0; i < dim_subproduct ; i++){
        ris[i+n] = f3_sum(ris[i+n], Q10[i]); //R1
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris ; i++){
        ris[i+2*n] = f3_sum(ris[i+2*n], Q4[i]); //R2
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+3*n] = f3_sum(ris[i+3*n], Q8[i]); //R3
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+4*n] = f3_sum(ris[i+4*n], Q2[i]); //R4
    }
    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
        ris[i+5*n] = f3_sum(ris[i+5*n], Q11[i]); //R5
    }
    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
        ris[i+6*n] = f3_sum(ris[i+6*n], P6[i]);
    }

    free(op_pointer);
    free(op_pointer_f9);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    return ris;
}

/*5_SPLIT IMPLEMENTATION*/

f9_element* split_5_f9(int m, f9_element* p1, f9_element* p2) {
    if (m < 14){ //Vero lim 32
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 5);
    int k = get_split_k_param(m, n, 5);

    f9_element* A0 = p1;
    f9_element* A1 = p1 + n;
    f9_element* A2 = p1 + 2 * n;
    f9_element* A3 = p1 + 3 * n;
    f9_element* A4 = p1 + 4 * n;

    f9_element* B0 = p2;
    f9_element* B1 = p2 + n;
    f9_element* B2 = p2 + 2 * n;
    f9_element* B3 = p2 + 3 * n;
    f9_element* B4 = p2 + 4 * n;

    printf("A0: ");
    print_vector_f9(A0, n);
    printf("A1: ");
    print_vector_f9(A1, n);
    printf("A2: ");
    print_vector_f9(A2, n);
    printf("A3: ");
    print_vector_f9(A3, n);
    printf("A4: ");
    print_vector_f9(A4, k);

    printf("B0: ");
    print_vector_f9(B0, n);
    printf("B1: ");
    print_vector_f9(B1, n);
    printf("B2: ");
    print_vector_f9(B2, n);
    printf("B3: ");
    print_vector_f9(B3, n);
    printf("B4: ");
    print_vector_f9(B4, k);

    int op_part1 = (34);
    int op_part2 = (25);
    f9_element* op_pointer = allocate_mem(op_part1, n, op_part2, (2*n-1));

    f9_element* S1 = op_pointer;
    sum_poly(n, k, A0, A4, S1); // S1 = A0 + A4
    f9_element* S2 = S1 + n;
    sum_poly(n, n, A1, A3, S2); // S2 = A1 + A3
    f9_element* S3 = S2 + n;
    diff_poly(n, k, A0, A4, S3); //S3 = A0 - A4
    f9_element* S4 = S3 + n;
    diff_poly(n, n, A1, A3, S4); //S4 = A1 - A3
    f9_element* S5 = S4 + n;
    sum_poly(n, n, S1, S2, S5); //S5 = S1 + S2
    f9_element* S6 = S5 + n;
    diff_poly(n, n, S1, A2, S6); //S6 = S1 - A2
    f9_element* S7 = S6 + n;
    sum_poly(n, n, S2, S3, S7); //S7 = S2 + S3
    f9_element* S8 = S7 + n;
    diff_poly(n, n, S2, S3, S8); //S8 = S2 - S3
    f9_element* S9 = S8 + n;
    diff_poly(n, n, S4, A2, S9); //S9 = S4 - A2
    f9_element* S10 = S9 + n;
    sum_poly(n, n, S4, A2, S10); //S10 = S4 + A2
    f9_element* S11 = S10 + n;
    sum_poly(n, n, S5, A2, S11); //S11 = S5 + A2 -> P1


    printf("S1: ");
    print_vector_f9(S1, n);
    printf("S2: ");
    print_vector_f9(S2, n);
    printf("S3: ");
    print_vector_f9(S3, n);
    printf("S4: ");
    print_vector_f9(S4, n);
    printf("S5: ");
    print_vector_f9(S5, n);
    printf("S6: ");
    print_vector_f9(S6, n);
    printf("S7: ");
    print_vector_f9(S7, n);
    printf("S8: ");
    print_vector_f9(S8, n);
    printf("S9: ");
    print_vector_f9(S9, n);
    printf("S10: ");
    print_vector_f9(S10, n);
    printf("S11: ");
    print_vector_f9(S11, n);


    printf("mem: ");
    //print_vector_f9(op_pointer, op_part1* n+ op_part2 * (2*n-1) );




    return NULL;
}