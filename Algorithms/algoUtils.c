#include "algoUtils.h"
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

void diff_poly_double_img_neg(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris){ //-P1 - wP2
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], f9_neg(p1[i])); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], f9_prod_img_neg(p2[i])); }
}

void print_vector_f3(int* v, int num_elements){
    for (int i = 0; i < num_elements-1; i++){
        printf("%d,",v[i]);
    }
    printf("%d\n",v[num_elements-1]);
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

void diff_poly_neg_img_f3(int terms_p1, int terms_p2, int* p1, int* p2, f9_element* ris){ // -P1 - F9(P2)w
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], get_f9_element(0, swap_bits(p1[i]))); }
    for(int i = 0; i < terms_p2; i++){ ris[i] = f9_sum(ris[i], get_f9_element(f9_neg(p2[i]), 0)); }
}

void diff_poly_pos_img_f3(int terms_p1, int terms_p2, int* p1, int* p2, f9_element* ris){ // -P1 + F9(P2)w
    for(int i = 0; i < terms_p1; i++){ ris[i] = f9_sum(ris[i], get_f9_element(0, swap_bits(p1[i]))); }
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