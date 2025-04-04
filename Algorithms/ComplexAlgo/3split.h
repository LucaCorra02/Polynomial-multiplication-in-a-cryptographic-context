#ifndef INC_3SPLIT_H
#define INC_3SPLIT_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include "../FieldImplementation/f3Utils.h"
    #include "../FieldImplementation/F9Utils.h"

    /*
        m = num termini polinomio
        i = grado split
        torna n in -> 2*n + k
    */
    int get_split_n_param(int m, int i );
    /*
        m = num termini polinomio
        n = parti uguali del polinomio
        torna k in -> 2*n + k = m -> k = m - (2*n)
     */
    int get_split_k_param(int m, int n);

    void print_vector_f9(f9_element* v, int num_elements);

    f9_element* allocate_mem(int num_array, int dim_array, int num_array_comp, int dim_array_comp);

    void sum_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris); //P1 + P2

    void diff_poly(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris); //P1 - P2

    void diff_poly_double(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris); // - P1 - P2

    void sum_poly_img(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris); // P1 + wP2

    void sum_poly_img_neg(int terms_p1, int terms_p2, f9_element* p1, f9_element* p2, f9_element* ris); //P1 - wP2

    f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2);

    f9_element* split_3_f9(int m, f9_element* p1, f9_element* p2);

    int* schoolbook_f3(int n, int* p1, int* p2);

    int* split_3_f3(int m, int* p1, int* p2);
#endif //INC_3SPLIT_H
