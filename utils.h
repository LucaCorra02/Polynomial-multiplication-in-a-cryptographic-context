#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_vector(char *filename, unsigned int num_operations,unsigned int operands, unsigned int operations[num_operations][operands]){ //Riempie il vettore operations con i dati presi da file.
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


