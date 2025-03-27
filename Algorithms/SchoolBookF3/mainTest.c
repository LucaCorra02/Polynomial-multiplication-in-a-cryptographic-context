#define BUFFERSIZE 100000
#define NUM_OPERANDS 1024

#include "f3schoolbook.h"

int main(int argc, char *argv[]){
    /*char buffer[BUFFERSIZE];
    while (fgets(buffer, BUFFERSIZE , stdin)){
        //printf("Read: %s", buffer);
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        int* p1 = split_operands(left,NUM_OPERANDS);
        int* p2 = split_operands(right,NUM_OPERANDS);
        int* ris = schoolbook_f3(NUM_OPERANDS,p1,p2);
        print_vector(ris,(2*NUM_OPERANDS)-1);
        free(p1);
        free(p2);
        free(ris);
    }*/

    char buffer[BUFFERSIZE];
    while (fgets(buffer, BUFFERSIZE , stdin)){
        //printf("Read: %s", buffer);
        char* left = strtok(buffer, ";");
        char* right = strtok(NULL, ";");
        f9_element* p1 = split_operands_f9(left,NUM_OPERANDS);
        f9_element* p2 = split_operands_f9(right,NUM_OPERANDS);
        f9_element* ris = schoolbook_f9(NUM_OPERANDS,p1,p2);
        print_vector_f9(ris,(2*NUM_OPERANDS)-1);
        free(p1);
        free(p2);
        free(ris);
    }

    return 0;
}
