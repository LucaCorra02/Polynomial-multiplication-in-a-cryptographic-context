#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "fileutils.h"

int main(int argc, char *argv[]) {
	if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    int num_rows = atoi(argv[2]), num_terms = atoi(argv[3]);
    int** p1 = create_vector(num_rows,num_terms);
    int** p2 = create_vector(num_rows,num_terms);

    if(read_file(argv[1], num_rows, num_terms, p1, p2) != 0){return 1;};
	for(int i = 0; i < num_rows; i++){
        int* ris = karatsuba(num_terms, p1[i], p2[i]);
        print_output_poly(ris,(num_terms*2)-1);
    }
    free_vector(p1, num_rows);
    free_vector(p2, num_rows);
    return 0;
}
