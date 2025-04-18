#include <stdlib.h>
#include "algorithms.h"

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