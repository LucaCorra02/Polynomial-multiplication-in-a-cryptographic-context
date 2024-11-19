#ifndef FILEUTILS_H
#define FILEUTILS_H

int** create_vector(int num_rows, int num_terms);

void free_vector(int** polynomials, int num_rows);

void print_polynomials(int **polynomials, int num_rows, int num_terms);

void print_output_poly(int* poly, int num_terms);

int read_file(char *filename, int num_rows, int num_terms, int** p1, int** p2);

#endif //FILEUTILS_H
