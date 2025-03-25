#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../FieldImplementation/f3Utils.h"
#include "../FieldImplementation/F9Utils.h"

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

int* split_operands(char* p, int num_operands){
    int i = 0;
    int* ris = calloc(num_operands,sizeof(int));
    char* token = strtok(p, ",");
    while(token != NULL && i < num_operands) {
        ris[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return ris;
}

void print_vector(int* v, int num_elements){
    for (int i = 0; i < num_elements-1; i++){
        printf("%d,",v[i]);
    }
    printf("%d\n",v[num_elements-1]);
}

#define BUFFERSIZE 10000
#define NUM_OPERANDS 1024

int main(int argc, char *argv[]){
    char buffer[BUFFERSIZE];
    while (fgets(buffer, BUFFERSIZE , stdin)){
        //printf("Read: %s", buffer);
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        int* p1 = split_operands(left,NUM_OPERANDS);
        int* p2 = split_operands(right,NUM_OPERANDS);
        int* ris = schoolbook_r(NUM_OPERANDS,p1,p2);
        print_vector(ris,(2*NUM_OPERANDS)-1);
        free(p1);
        free(p2);
        free(ris);
    }
    //f9_element a = get_f9_element(1,2);
    //print_f9_element(a);
    return 0;
}