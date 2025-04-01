#include "3split.h"

#define BUFFERSIZE 10000
#define NUM_OPERANDS 1024

int main(int argc, char *argv[]){

    int i = 3;

    for (int m = 6; m < 3000; m++){
        int n = get_split_n_param(m, i);
        int k = get_split_k_param(m, n);
        printf("Grado partenza: %d, n = %d, k = %d, ris = %d\n", m, n, k, 2*n+k);
    }

}

