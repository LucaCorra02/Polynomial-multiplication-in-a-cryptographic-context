#include "f3Utils.h"
#include "getTime.h"
#include "utils.h"

typedef struct f9_element {unsigned int real; unsigned int imaginary;} f9_element;

void print_f9_element(f9_element n) {
  printf("real: %d, i: %d\n",n.real,n.imaginary);
}

f9_element get_f9_element(int real, int imaginary) {
  real = abs_f3(real);
  imaginary = abs_f3(imaginary);
  f9_element ris;
  ris.real = real,ris.imaginary = imaginary;
  return ris;
}

f9_element f9_sum(f9_element a, f9_element b) {
	f9_element ris;
  	ris.real = f3_sum(a.real,b.real);
    ris.imaginary = f3_sum(a.imaginary,b.imaginary);
    return ris;
}

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
  f9_element a = get_f9_element(150,-1);
  f9_element b = get_f9_element(2,1);
  f9_element ris = f9_sum(a,b);
  print_f9_element(ris);
}
