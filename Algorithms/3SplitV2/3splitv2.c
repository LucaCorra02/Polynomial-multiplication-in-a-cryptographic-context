#include "3split.h"
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
int get_split_k_param(int m, int n){ return  m - (2*n); }
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

void sum_poly_img_neg(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ //P1 - wP2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_prod_img_neg(p2[i])); }
}

f9_element* split_3_v2_f9(int m, f9_element* p1, f9_element* p2){
    if (m < 6){
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n);

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


    /*print_vector_f9(op_pointer, n * op_part1 + (2*n-1) * op_part2);
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
    printf("S1_b: ");
    print_vector_f9(S1_b, n);
    printf("S2_b: ");
    print_vector_f9(S2_b, n);
    printf("S3_b: ");
    print_vector_f9(S3_b, n);
    printf("S4_b: ");
    print_vector_f9(S4_b, n);
    printf("S5_b: ");
    print_vector_f9(S5_b, n);
     */

    f9_element* P0 = schoolbook_f9(n, A0, B0);
    f9_element* P1 = schoolbook_f9(n, S5, S5_b);
    f9_element* P2 = schoolbook_f9(n, S2, S2_b);
    f9_element* P3 = schoolbook_f9(n, S3, S3_b);
    f9_element* P4 = schoolbook_f9(k, A2, B2);

    int dim_subproduct = (2*n-1);
    int dim_subproduct_rem = (2*k-1);

    /*printf("P0: ");
    print_vector_f9(P0, dim_subproduct);
    printf("P1: ");
    print_vector_f9(P1, dim_subproduct);
    printf("P2: ");
    print_vector_f9(P2, dim_subproduct);
    printf("P3: ");
    print_vector_f9(P3, dim_subproduct);
    printf("P4: ");
    print_vector_f9(P4, dim_subproduct_rem);
     */

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

    /*printf("Q1: ");
    print_vector_f9(Q1, dim_subproduct);
    printf("Q2: ");
    print_vector_f9(Q2, dim_subproduct);
    printf("Q3: ");
    print_vector_f9(Q3, dim_subproduct);
    printf("Q4: ");
    print_vector_f9(Q4, dim_subproduct);
    printf("Q5: ");
    print_vector_f9(Q5, dim_subproduct);
    printf("Q6: ");
    print_vector_f9(Q6, dim_subproduct);
    printf("Q7: ");
    print_vector_f9(Q7, dim_subproduct);
    printf("Q8: ");
    print_vector_f9(Q8, dim_subproduct);
    */

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

void sum_poly_img_f3(int terms_p1, int terms_p2, int* p1, int* p2, f9_element* ris){ // F9(P1) + F9(P2)w
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], get_f9_element(0, p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], get_f9_element(p2[i], 0)); }
}

void diff_poly_img_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 - F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_imaginary_part(p2[i]))); }
}

void sum_poly_imag_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 + F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], get_imaginary_part(p2[i])); }
}

void diff_poly_real_f3(int terms_p1, int terms_p2, int* p1, f9_element* p2, int* ris){ // P1 + F9(P2_imag_part)
    for(int i = 0; i < terms_p1; i++){ ris[i] = f3_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f3_sum(ris[i], swap_bits(get_real_part(p2[i]))); }
}

int* split_3_f3(int m, int* p1, int* p2){
	/*if (m < 6){
        return schoolbook_f3(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n);

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
	 */
    return NULL;
}
