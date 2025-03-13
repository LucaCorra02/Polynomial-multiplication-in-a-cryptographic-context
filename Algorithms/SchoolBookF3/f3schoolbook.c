#include <stdio.h>
#include <stdlib.h>
#include "f3Utils.h"

int* schoolbook_r(int n, int* p1, int* p2) {
    int dim_ris = (2 * n) - 1;
    int* ris = calloc(dim_ris, sizeof(int));
    if (n == 1) { ris[0] = f3_prod(int_to_f3(p1[0]),int_to_f3(p2[0])); return ris; }

    int max_deg = n - 1;
    unsigned int mst_p1 = int_to_f3(p1[max_deg]);
    unsigned int mst_p2 = int_to_f3(p2[max_deg]);
    ris[max_deg * 2] = f3_sum(int_to_f3(ris[max_deg * 2]), f3_prod(mst_p1,mst_p2));

    for (int i = 0; i < max_deg; i++) {
        ris[max_deg + i] = f3_sum(ris[max_deg + i], f3_prod(mst_p1, int_to_f3(p2[i])));
        ris[max_deg + i] = f3_sum(ris[max_deg + i], f3_prod(mst_p2, int_to_f3(p1[i])));
    }

    int* sub_result = schoolbook_r(n - 1, p1, p2);
    for (int i = 0; i < (dim_ris - 1); i++) {
        ris[i] = f3_sum(ris[i],sub_result[i]);
    }

    free(sub_result);
    return ris;
}



int main(int argc, char *argv[]){
    int p1[] = {11, 298, 323, 442, 97, 920, 79, 122};
    int p2[] = {490, 323, 210, 1000, 210, 5, 33, 210};
    int n = 8;
    int* ris = schoolbook_r(n,p1,p2);
    for (int i = 0; i < (2*n)-1; i++){
        printf("%d, ",ris[i]);
    }
    printf("\n");
    free(ris);
}