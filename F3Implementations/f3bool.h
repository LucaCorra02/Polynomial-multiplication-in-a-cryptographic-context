#ifndef F3BOOL_H
#define F3BOOL_H

typedef struct {
    long double total_time;
    long double mean_time;
    int result;
} results;

typedef struct f3_element {bool bits[2];} f3_element;

#define CHECK_BIT(n,pos) ((n) & (1<<(pos))) //macro per controllare se l'n-esimo bit è settato.

unsigned int f3_to_int_bool(f3_element f3);

f3_element int_to_f3_bool(unsigned int n);

void print_f3_element(f3_element f3);

void print_binary_bool(unsigned int n);

f3_element f3_sum_bool(f3_element a, f3_element b);

f3_element f3_prod_bool(f3_element a, f3_element b);

#endif //F3BOOL_H
