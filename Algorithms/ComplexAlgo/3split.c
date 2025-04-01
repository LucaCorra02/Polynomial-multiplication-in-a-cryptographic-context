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

f9_element* allocate_mem(int num_array, int dim_array){
  return calloc(num_array * dim_array, sizeof(f9_element));
}

void sum_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(int_to_f9_element(ris[i]), int_to_f9_element(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(int_to_f9_element(ris[i]), int_to_f9_element(p2[i])); }
}

void diff_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], p1[i]); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_neg(p2[i])); }
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
    print_vector_f9(A0, n);
    print_vector_f9(A1, n);
    print_vector_f9(A2, k);
    /*
        f9_element* B0 = p2;
        f9_element* B1 = p2 + n;
        f9_element* B2 = p2 + 2*n;
     */
    f9_element* op_pointer = allocate_mem(6, n);

    f9_element* S1 = op_pointer;
    sum_poly(n,k,A0,A2,S1); // A0 + A2
    f9_element* S2 = op_pointer + n;
    sum_poly(n,n,S1,A1,S2); // S1 + A1
    f9_element* S3 = op_pointer + 2*n;
    diff_poly(n,n,S1,A1,S3);// S2 - A1
    f9_element* S4 = op_pointer + 3*n;
    diff_poly(n,k,A0,A2,S4); // A0 - A2


    print_vector_f9(op_pointer, 6*n);
    print_vector_f9(S1, n);
    print_vector_f9(S2, n);
    print_vector_f9(S3, n);

    /*
        print_vector_f9(A0, n);

        print_vector_f9(A1, n);
        print_vector_f9(A2, k);

        print_vector_f9(B0, n);
        print_vector_f9(B1, n);
        print_vector_f9(B2, k);
    */






    return NULL;
}
