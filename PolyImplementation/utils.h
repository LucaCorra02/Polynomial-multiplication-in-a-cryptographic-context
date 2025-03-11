#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int** create_vector(unsigned int num_operations, unsigned int num_operands) {
    unsigned int **operations = malloc(num_operations * sizeof(unsigned int *));
    for (int i = 0; i < num_operations; i++) {
        operations[i] = malloc(num_operands * sizeof(unsigned int));
    }
    return operations;
}

void free_vector(unsigned int **operations, unsigned int num_operations) {
    for (int i = 0; i < num_operations; i++) {
        free(operations[i]);
    }
    free(operations);
}

int load_vector(char *filename, unsigned int num_operations, unsigned int **operations){ //Riempie il vettore operations con i dati presi da file.
    FILE *fp = fopen(filename, "r");
    if(fp != NULL) {
        char str[100];
        unsigned int cont = 0;
        while(fgets(str,100, fp) && cont < num_operations) {
            char * token = strtok (str,",");
            int i = 0;
            while (token != NULL) {
                operations[cont][i] = atoi(token);
                i++;
                token = strtok(0,",");
            }
            cont++;
        }
    } else {
        fprintf(stderr, "error\n");
        return 1;
    }
    fclose(fp);
    return 0;
}

int read_file(char *filename, unsigned int num_operations, unsigned int** operations) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore apertura file");
        return 1;
    }
    char line[256];
    unsigned int cont = 0;
    while (fgets(line, sizeof(line), file) != NULL && cont < num_operations) {
        char *part1 = strtok(line, ";"), *part2 = strtok(NULL, ";");
        if (part1 && part2) {
            char *a1 = strtok(part1, ","), *a0 = strtok(NULL, ",");
            char *b1 = strtok(part2, ","), *b0 = strtok(NULL, ",");
            if (a1 && a0 && b1 && b0) {
                int a1_img = atoi(a1), a0_real = atoi(a0);
                int b1_img = atoi(b1), b0_real = atoi(b0);
                operations[cont][0] = a1_img , operations[cont][1] = a0_real;
                operations[cont][2] = b1_img , operations[cont][3] = b0_real;
            }
        }
        cont++;
    }
    fclose(file);
    return 0;
}


