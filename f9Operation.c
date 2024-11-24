#include "f3Utils.h"
#include "getTime.h"
#include "utils.h"

/*
	make all
	./f9Operation.out
 */

typedef unsigned int f9_element; // 4 bits a3a2a1a0, dove a3a2 rappresentano la parte immaginaria e a1a0 rappresentano la parte reale

unsigned int get_real_part(f9_element element){
	return kth_bit(element,1)*2 + kth_bit(element,0);
}

unsigned int get_imaginary_part(f9_element element){
  return element >> 2; //Shift a destra di due
}

void print_f9_element(f9_element n) {
  printf("%dw + %d\n",get_imaginary_part(n),get_real_part(n));
}

f9_element get_f9_element(int imaginary, int real) {
  imaginary = int_to_f3(imaginary);
  real = int_to_f3(real);
  return (imaginary << 2) | real; // Shifto di 2 la parte immaginaria e poi metto in or la parte reale
}

f9_element f9_sum(f9_element a, f9_element b) {
    return (f3_sum(get_imaginary_part(a) , get_imaginary_part(b)) << 2 ) | f3_sum(get_real_part(a) , get_real_part(b));
}

f9_element f9_prod(f9_element a, f9_element b) {
	unsigned int a1 = get_imaginary_part(a), a0 = get_real_part(a);
	unsigned int b1 = get_imaginary_part(b), b0 = get_real_part(b);
	int neg_prod  = f3_prod(a1,b1);
	swap_bits(&neg_prod, 0 , 1);
    return (f3_sum(f3_prod(a0,b1),f3_prod(a1,b0)) << 2 ) | f3_sum(f3_prod(a0,b0),neg_prod);
}

long double benchmark(f9_element f9_operation(f9_element a, f9_element b),unsigned int num_operations, unsigned int** operations){
  	long double total_time = 0.0;
    long double start_time = 0.0;
    long double end_time = 0.0;
    int i;

    start_time = get_current_time();
   	for (i=0; i < num_operations; i++) {
		f9_element a = get_f9_element(operations[i][0],operations[i][1]);
		f9_element b = get_f9_element(operations[i][2],operations[i][3]);
		f9_element ris = f9_prod(a,b);
		print_f9_element(ris);
	}
    end_time = get_current_time();
    total_time = end_time - start_time;
    return total_time;
}


int main(int argc, char *argv[]) { //ARGV = file_name , file_rows, num_operands
	if (argc < 4) {
        fprintf(stderr, "No args\n");
        return 1;
    }
    unsigned int file_rows = atoi(argv[2]), num_operands = atoi(argv[3]);
	unsigned int** operations = create_vector(file_rows, num_operands);

    if (read_file(argv[1],file_rows,operations) != 0) return 1;
   	long double total_time = benchmark(f9_prod,file_rows, operations);
    printf("%Lfs\n", total_time);
    free_vector(operations, file_rows);


    /*
    	Con *(char*)&a ottengo il puntatore (1 byte) al byte meno significativo (intero a 32 bit è su 4 byte).
    	Eseguo una maschera 0...01 per esterra il LSB.

		unsigned int a = 1;
		printf("MSB: %d\n",(*(char*)&a & 2) >> 1);
		printf("LSB: %d\n",*(char*)&a & 1);

		int n = 3;
		swap_bits(&n,1,0);
		print_binary(n);

     */

    return 0;
}

