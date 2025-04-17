#include "4split.h"
#include <omp.h>

/*
    m = num termini polinomio
    i = grado split
    torna n in -> 2*n + k
 */
int get_split_n_param(int m, int i ){ return ceil(((double)m)/i); }
/*
    m = num termini polinomio
    n = parti uguali del polinomio
    torna k in -> 2*n + k = m -> k = m - (2*n)
 */
int get_split_k_param(int m, int n, int i){ return  m - ((i-1)*n); }
/*
    n = numero termini p1 e p2;
    p1 = puntatore polinomio1
    p2 = puntatore polinomio2
 */

void print_vector_f9(f9_element* v, int num_elements){
    for (int i = 0; i < num_elements-1; i++){
        f9_element img = get_imaginary_part(v[i]);
        f9_element real = get_real_part(v[i]);
        printf("(%di + %d),",img,real);
    }
    f9_element img = get_imaginary_part(v[num_elements-1]);
    f9_element real = get_real_part(v[num_elements-1]);
    printf("(%di + %d)\n",img,real);
}

f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2) { //coefficenti solo in f9
    int dim_ris = (2 * n) - 1;
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));
    if (n == 1){
        ris[0] = f9_prod(int_to_f9_element(p1[0]),int_to_f9_element(p2[0]));
        return ris;
    }
    int max_deg = n - 1;
    unsigned int mst_p1 = p1[max_deg];
    unsigned int mst_p2 = p2[max_deg];
    ris[max_deg * 2] = f9_sum(ris[max_deg * 2], f9_prod(mst_p1,mst_p2));

    for (int i = 0; i < max_deg; i++) {
        ris[max_deg + i] = f9_sum(int_to_f9_element(ris[max_deg + i]), f9_prod(mst_p1, int_to_f9_element(p2[i])));
        ris[max_deg + i] = f9_sum(int_to_f9_element(ris[max_deg + i]), f9_prod(mst_p2, int_to_f9_element(p1[i])));
    }

    //print_vector(ris,dim_ris);
    f9_element* sub_result = schoolbook_f9(n - 1, p1, p2);
    for (int i = 0; i < (dim_ris - 1); i++) {
        ris[i] = f9_sum(int_to_f9_element(ris[i]),int_to_f9_element(sub_result[i]));
    }

    free(sub_result);
    return ris;
}

f9_element* allocate_mem(int num_array, int dim_array, int num_array_comp, int dim_array_comp){
  int dim_first_part = num_array * dim_array;
  int dim_second_part = num_array_comp * dim_array_comp;
  return calloc(dim_first_part + dim_second_part, sizeof(f9_element));
}

void sum_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ // P1 + P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], p2[i]); }
}

void diff_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ // P1 - P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_neg(p2[i])); }
}

void diff_poly_double(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ // - P1 - P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], f9_neg(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_neg(p2[i])); }
}

void sum_poly_img(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ //P1 + wP2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_prod_img(p2[i])); }
}

void neg_sum_poly_img(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ // -P1 + wP2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], f9_neg(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_prod_img(p2[i])); }
}

void sum_poly_img_neg(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ //P1 - wP2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_prod_img_neg(p2[i])); }
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

void print_vector_f3(int* v, int num_elements){
    for (int i = 0; i < num_elements-1; i++){
        printf("%d,",v[i]);
    }
    printf("%d\n",v[num_elements-1]);
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

int* allocate_mem_f3(int num_array, int dim_array, int num_array_comp, int dim_array_comp){
  int dim_first_part = num_array * dim_array;
  int dim_second_part = num_array_comp * dim_array_comp;
  return calloc(dim_first_part + dim_second_part, sizeof(int));
}

void sum_poly_f3(int terms_p1, int terms_p2, int* p1, int* p2, int* ris){ // P1 + P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], p2[i]); }
}

void diff_poly_f3(int terms_p1, int terms_p2, int* p1, int* p2, int* ris){ // P1 - P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(p2[i])); }
}

void diff_poly_double_f3(int terms_p1, int terms_p2, int* p1, int* p2, int* ris){ // -P1 -P2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], swap_bits(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(p2[i])); }
}

void sum_poly_img_f3(int terms_p1, int terms_p2, int* p1, int* p2, f9_element* ris){ // F9(P1) + F9(P2)w
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], get_f9_element(0, p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], get_f9_element(p2[i], 0)); }
}

void sum_poly_neg_img_f3(int terms_p1, int terms_p2, int* p1, int* p2, f9_element* ris){ // F9(P1) - F9(P2)w
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], get_f9_element(0, p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], get_f9_element(f9_neg(p2[i]), 0)); }
}

void diff_poly_img_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 - F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_imaginary_part(p2[i]))); }
}

void sum_poly_imag_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 + F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_imaginary_part(p2[i])); }
}

void diff_double_poly_imag_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // - P1 - P2_imag_part
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], swap_bits(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_imaginary_part(p2[i]))); }
}

void diff_single_poly_imag_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // - P1 + P2_imag_part
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], swap_bits(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_imaginary_part(p2[i])); }
}

void diff_poly_real_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 - F9(P2_real_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_real_part(p2[i]))); }
}

void sum_poly_real_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 + F9(P2_real_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_real_part(p2[i])); }
}

void diff_double_poly_real_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // - P1 - P2_real_part
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], swap_bits(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_real_part(p2[i]))); }
}

void sum_poly_double_real_f3(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, int* ris){ // F9(P1_real_part) + F9(P2_real_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], get_real_part(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_real_part(p2[i])); }
}

void sum_poly_real_img_f3(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, int* ris){ // F9(P1_real_part) + F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], get_real_part(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_imaginary_part(p2[i])); }
}

int* split_4_f3(int m, int* p1, int* p2){
    if (m < 6){
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

    printf("S1: ");
    print_vector_f3(S1, n);
    printf("S2: ");
    print_vector_f3(S2, n);
    printf("S3: ");
    print_vector_f3(S3, n);
    printf("S4: ");
    print_vector_f3(S4, n);
    printf("S5: ");
    print_vector_f3(S5, n);
    printf("S6: ");
    print_vector_f3(S6, n);
    printf("S7: ");
    print_vector_f3(S7, n);
    printf("S8: ");
    print_vector_f9(S8, n);
    printf("S9: ");
    print_vector_f9(S9, n);
    printf("S10: ");
    print_vector_f9(S10, n);
    printf("S11: ");
    print_vector_f9(S11, n);
    printf("S1_b: ");
    print_vector_f3(S1_b, n);
    printf("S2_b: ");
    print_vector_f3(S2_b, n);
    printf("S3_b: ");
    print_vector_f3(S3_b, n);
    printf("S4_b: ");
    print_vector_f3(S4_b, n);
    printf("S5_b: ");
    print_vector_f3(S5_b, n);
    printf("S6_b: ");
    print_vector_f3(S6_b, n);
    printf("S7_b: ");
    print_vector_f3(S7_b, n);
    printf("S8_b: ");
    print_vector_f9(S8_b, n);
    printf("S9_b: ");
    print_vector_f9(S9_b, n);
    printf("S10_b: ");
    print_vector_f9(S10_b, n);
    printf("S11_b: ");
    print_vector_f9(S11_b, n);

    int *P0, *P1, *P6;
    f9_element *P2, *P3, *P4, *P5;
    P0 = schoolbook_f3(n, A0, B0);
    P1 = schoolbook_f3(n, S4, S4_b);
    P2 = schoolbook_f9(n, S8, S8_b);
    P3 = schoolbook_f9(n, S9, S9_b);
    P4 = schoolbook_f9(n, S10, S10_b);
    P5 = schoolbook_f9(n, S11, S11_b);
    P6 = schoolbook_f3(k, A3, B3);

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    printf("P0: ");
    print_vector_f3(P0, dim_subproduct);
    printf("P1: ");
    print_vector_f3(P1, dim_subproduct);
    printf("P2: ");
    print_vector_f9(P2, dim_subproduct);
    printf("P3: ");
    print_vector_f9(P3, dim_subproduct);
    printf("P4: ");
    print_vector_f9(P4, dim_subproduct);
    printf("P5: ");
    print_vector_f9(P5, dim_subproduct);
    printf("P6: ");
    print_vector_f3(P6, dim_subproduct_rem);

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



    printf("Q1: ");
    print_vector_f3(Q1, dim_subproduct);
    printf("Q2: ");
    print_vector_f3(Q2, dim_subproduct);
    printf("Q3: ");
    print_vector_f3(Q3, dim_subproduct);
    printf("Q4: ");
    print_vector_f3(Q4, dim_subproduct);
    printf("Q5: ");
    print_vector_f3(Q5, dim_subproduct);
    printf("Q6: ");
    print_vector_f3(Q6, dim_subproduct);
    printf("Q7: ");
    print_vector_f3(Q7, dim_subproduct);
    printf("Q8: ");
    print_vector_f3(Q8, dim_subproduct);
    printf("Q9: ");
    print_vector_f3(Q9, dim_subproduct);
    printf("Q10: ");
    print_vector_f3(Q10, dim_subproduct);
    printf("Q11: ");
    print_vector_f3(Q11, dim_subproduct);

    printf("Spazio F9: ");
    print_vector_f9(op_pointer_f9, (n) * 8);
    printf("Spazio F3: ");
    print_vector_f3(op_pointer, n*op_part1 + op_part2*(2*n-1));

    return NULL;
}
