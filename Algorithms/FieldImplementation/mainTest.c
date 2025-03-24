#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f3Utils.h"
#include "f9Utils.h"

int main(int argc, char *argv[]){
    int a = 3;
    int b = 2;
    unsigned int f3_a = int_to_f3(a);
    unsigned int f3_b = int_to_f3(b);
    unsigned int ris = f3_sum(f3_a, f3_b);
    printf("ris = %d\n", ris);

    f9_element f9_a = f3_a;
    f9_element f9_b = f3_b;
    print_f9_element(f3_b);

    return 0;
}

