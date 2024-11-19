#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileutils.h"

int** create_vector(int num_rows, int num_terms) {
    int **polynomials = malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++) {
        polynomials[i] = malloc(num_terms * sizeof(int));
    }
    return polynomials;
}

void free_vector(int** polynomials, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(polynomials[i]);
    }
    free(polynomials);
}

void print_polynomials(int **polynomials, int num_rows, int num_terms) {
  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_terms; j++) {
      printf("%d ", polynomials[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_output_poly(int* poly, int num_terms){
    for(int i = 0; i < num_terms-1; i++){
        printf("%d,",poly[i]);
    }
    printf("%d\n",poly[num_terms-1]);
}

int read_file(char *filename, int num_rows, int num_terms, int** p1, int** p2) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore apertura file");
        return 1;
    }
    char line[256];
    unsigned int cont = 0;
    while (fgets(line, sizeof(line), file) != NULL && cont < num_rows) {
        char *part1 = strtok(line, ";");
        char *part2 = strtok(NULL, ";");
        if (part1 && part2) {
            int i = 0;
            char *token = strtok(part1, ",");
            while (token && i < num_terms) {
                p1[cont][i] = atoi(token);
                token = strtok(NULL, ",");
                i++;
            }

            // Parsing della seconda parte
            int j = 0;
            char *token2 = strtok(part2, ",");
            while (token2 && j < num_terms) {
                p2[cont][j] = atoi(token2);
                token2 = strtok(NULL, ",");
                j++;
            }
        }
        cont++;
    }
    fclose(file);
    return 0;
}

