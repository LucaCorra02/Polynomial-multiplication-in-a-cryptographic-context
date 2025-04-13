#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "karatsubaField.h"

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

f9_element* split_operands_f9(char* p, int num_operands){
    f9_element* ris = calloc(num_operands,sizeof(f9_element));
    int i = 0;
    char* token = strtok(p, ",");
    while (token != NULL && i < num_operands) {
        int real, imag = 0;
        sscanf(token, "%d:%d", &imag, &real);
        ris[i++] = get_f9_element(imag,real);
        token = strtok(NULL, ",");
    }
    return ris;
}

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

#define BUFFERSIZE 10000
#define NUM_OPERANDS 1024

int main(int argc, char *argv[]){

    int num_operands = NUM_OPERANDS;
    int buffer_size = BUFFERSIZE;

    char buffer[buffer_size];
    while (fgets(buffer, buffer_size , stdin)){
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        int* p1 = split_operands(left, num_operands);
        int* p2 = split_operands(right, num_operands);
        int* ris = unbalanced_karatsuba_f3(num_operands, p1, p2);
        print_vector(ris, (2*num_operands)-1);
        free(p1);
        free(p2);
        free(ris);
    }
    /*
    char buffer[BUFFERSIZE];
    while (fgets(buffer, BUFFERSIZE , stdin)){
        //printf("Read: %s", buffer);
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        f9_element* p1 = split_operands_f9(left,NUM_OPERANDS);
        f9_element* p2 = split_operands_f9(right,NUM_OPERANDS);
        f9_element* ris = unbalanced_karatsuba_f9(NUM_OPERANDS,p1,p2);
        print_vector_f9(ris,(2*NUM_OPERANDS)-1);
        free(p1);
        free(p2);
        free(ris);
    }
     */

    return 0;
}