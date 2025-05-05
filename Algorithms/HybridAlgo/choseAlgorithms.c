#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

NextAlgorithms choose_next_algo(int n, int* p1, int* p2){
  	if (n%2 == 0){
        //printf("Con n = %d, scelgo karatsuba\n",n);
    	return karatsuba;
    }
    //return schoolbook_r
    //printf("Con n = %d, scelgo unbalanced_karatsuba\n",n);
    return unbalanced_karatsuba;
}


