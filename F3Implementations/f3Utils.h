#define F3UTILS_H


extern const unsigned int LSB_I; //la posizione del bit meno significativo
extern const unsigned int MSB_I; //posizione bit più significativo
extern const unsigned int look_up_table[];

unsigned int mod (int a, int b);

unsigned int int_to_F3(int n);

unsigned int kth_bit(unsigned int n, unsigned int k); //ritorna il k-esimo bit di n. In modo da non avere array.

void print_binary(unsigned int n); //stampa rappresentazione binaria di un intero.

