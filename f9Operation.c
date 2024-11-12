#include "f3Utils.h"
#include "getTime.h"
#include "utils.h"

/*
	make all
	./f9Operation.out
 */

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

f9_element f9_prod(f9_element a, f9_element b) {
	unsigned int a1 = a.imaginary, a0 = a.real;
	unsigned int b1 = b.imaginary, b0 = b.real;

	unsigned int a0b1 = f3_prod(a0,b1);
    unsigned int a1b0 = f3_prod(a1,b0);
    unsigned int a0b0 = f3_prod(a0,b0);
    unsigned int a1b1 = f3_prod(a1,b1);

   	f9_element ris;
    ris.real = f3_sum(a0b1,a1b0);
	ris.imaginary = f3_sum(a0b0,abs_f3(a1b1));
    return ris;
}

int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
  /*
	printf("%s %s\n",argv[1],argv[3]);
  	f9_element a = get_f9_element(0,1);
  	f9_element b = get_f9_element(2,0);
  	f9_element ris = f9_prod(a,b);
  	print_f9_element(ris);
 */
	if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
    unsigned int operations[file_rows][num_operands];
    if (read_file(argv[1],file_rows,num_operands, operations) != 0) return 1;

    for (int i = 0; i < file_rows; i++) {
    	f9_element a = get_f9_element(operations[i][0],operations[i][1]);
        f9_element b = get_f9_element(operations[i][2],operations[i][3]);
        f9_element ris = f9_prod(a,b);
      	print_f9_element(ris);
    }

    //printf("A: (img: %d,real: %d), B: (img: %d,real: %d)\n", operations[3][0], operations[3][1], operations[3][2], operations[3][4]);
}

