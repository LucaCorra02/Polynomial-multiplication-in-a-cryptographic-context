#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fileutils.h"

//considero polinomi su 32 bit
//funzione con grado pollinmimio, legge da un file che prodotto utilizzare

/*
    cd ..
    make all
    cd Schoolbook
    ./schoolbook.out ../PolyTest/TestFile/LowDeg/lowDeg.txt 10000 10


 */

int* schoolbook_recursive(int n, int* p1, int* p2, int* ris){
    if(n==0){return ris;} //caso di uscita
    int max_deg = n - 1;
    int mst_p1 = p1[max_deg]; //termine di grado massimo
    int mst_p2 = p2[max_deg];
    ris[max_deg * 2] += mst_p1 * mst_p2;

    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p1 * p2[i];
    }
    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p2 * p1[i];
    }
    return schoolbook_recursive(n - 1, p1, p2, ris);
}

int* schoolbook_r(int n, int* p1, int* p2) { //n = numero di termini.
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloca e inizializza.
    if (n==1) {ris[0] = p1[0] * p2[0]; return ris;} // Caso base, evito la chimata ricorsiva.
    return schoolbook_recursive(n, p1, p2, ris);
}

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
        int* ris = schoolbook_r(num_terms, p1[i], p2[i]);
        print_output_poly(ris,(num_terms*2)-1);
    }
    free_vector(p1, num_rows);
    free_vector(p2, num_rows);
    return 0;
}
