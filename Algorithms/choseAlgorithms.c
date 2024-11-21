#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

NextAlgorithms choose_next_algo(int n, int* p1, int* p2){
      if (n%2 == 0){
        printf("Scelgo karatsuba con n = %d \n",n);
        return karatsuba;
      }
      printf("Scelgo School con n = %d\n",n);
      return schoolbook_r;
}


