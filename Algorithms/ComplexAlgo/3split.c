#include "3split.h"

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
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(int_to_f9_element(ris[i]), int_to_f9_element(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(int_to_f9_element(ris[i]), int_to_f9_element(p2[i])); }
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

f9_element* split_3_f9(int m, f9_element* p1, f9_element* p2){
    if (m < 6){
        printf("Caso Base");
        return schoolbook_f9(m, p1, p2);
    }
    int n = get_split_n_param(m, 3);
    int k = get_split_k_param(m, n);
    printf("Params: %d, %d\n", n, k);

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

    f9_element* P0 = schoolbook_f9(n, A0, B0);
    f9_element* P1 = schoolbook_f9(n, S2, S2_b);
    f9_element* P2 = schoolbook_f9(n, S3, S3_b);
    f9_element* P3 = schoolbook_f9(n, S5, S5_b);
    f9_element* P4 = schoolbook_f9(k, A2, B2);

    printf("P0: ");
    print_vector_f9(P0, 2*n-1);
    printf("P1: ");
    print_vector_f9(P1, 2*n-1);
    printf("P2: ");
    print_vector_f9(P2, 2*n-1);
    printf("P3: ");
    print_vector_f9(P3, 2*n-1);
    printf("P4: ");
    print_vector_f9(P4, 2*k-1);

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


    printf("sos:%d\n",(op_part1*n)+(op_part2*(2*n-1)));
    print_vector_f9(op_pointer, (op_part1*n)+(op_part2*(2*n-1)));

    printf("\nQ1: ");
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

    int dim_ris = (2*m-1);
    f9_element* ris = calloc(dim_ris, sizeof(f9_element));

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i] = f9_sum(ris[i], P0[i]);
    }
    printf("ris P0: ");
    print_vector_f9(ris, dim_ris);

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+n] = f9_sum(ris[i+n], Q7[i]);
    }
    printf("ris R1: ");
    print_vector_f9(ris, dim_ris);

    for(int i = 0; i < dim_subproduct ; i++){
    	ris[i+2*n] = f9_sum(ris[i+2*n], Q4[i]);
    }
    printf("ris R2: ");
    print_vector_f9(ris, dim_ris);

    for(int i = 0; i < dim_subproduct && i < dim_ris  ; i++){
    	ris[i+3*n] = f9_sum(ris[i+3*n], Q8[i]);
    }
    printf("ris R3: ");
    print_vector_f9(ris, dim_ris);

    for(int i = 0; i < dim_subproduct_rem && i < dim_ris; i++){
    	ris[i+4*n] = f9_sum(ris[i+4*n], P4[i]);
    }
    printf("ris R4: ");
    print_vector_f9(ris, dim_ris);

    free(op_pointer);
    free(P0);
    free(P1);
    free(P2);
    free(P3);
    free(P4);
    return ris;
}
