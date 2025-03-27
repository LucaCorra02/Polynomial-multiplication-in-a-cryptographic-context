#ifndef F3SCHOOLBOOK_H
#define F3SCHOOLBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../FieldImplementation/f3Utils.h"
#include "../FieldImplementation/F9Utils.h"

int* split_operands(char* p, int num_operands);

void print_vector(int* v, int num_elements);

int* schoolbook_f3(int n, int* p1, int* p2);

f9_element* split_operands_f9(char* p, int num_operands);

void print_vector_f9(f9_element* v, int num_elements);

f9_element* schoolbook_f9(int n, f9_element* p1, f9_element* p2);

#endif //F3SCHOOLBOOK_H
