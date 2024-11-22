#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

NextAlgorithms choose_next_algo(int n, int* p1, int* p2){
  	if (n%2 == 0){
    	return karatsuba;
    }
    return schoolbook_r;
}


