import numpy as np
import random
import sys

def gen_random_compleate_poly(n_terms,max_coff):
    coff_a = []
    coff_b = []
    for i in range (0,n_terms):
        term_a = random.randint(1, max_coff)
        term_b = random.randint(1, max_coff)
        coff_a.append(term_a)
        coff_b.append(term_b)
    return coff_a, coff_b

def print_input(coff_a, coff_b):
    print(*coff_a, sep=',',end='')
    print(";",end='')
    print(*coff_b, sep=',')

def calc_prod(coff_a, coff_b):
    coff_a.reverse(),coff_b.reverse()
    p1d, p2d = np.poly1d(coff_a), np.poly1d(coff_b)
    p1,p2 = np.polynomial.Polynomial(p1d.coef[::-1]),np.polynomial.Polynomial(p2d.coef[::-1])
    #print("(",p1,")"," * ","(",p2,")")
    ris = np.polymul(p1d,p2d)
    #print(np.polynomial.Polynomial(ris.coef[::-1]))
    return ris

def print_prod(ris):
    np.sort(ris)
    rev = []
    for i in range(0,len(ris)+1):
        rev.append(ris[i])
    print(*rev, sep=',')

def gen_correct_output_prod(file_name):
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            coff_a = [int(coff) for coff in tmp[0].split(',')]
            coff_b = [int(coff) for coff in tmp[1].split(',')]
            print_prod(calc_prod(coff_a,coff_b))

def gen_correct_input(rows,n_terms,max_coff):
    for i in range (0,rows):
        coff_a,coff_b = gen_random_compleate_poly(n_terms,max_coff)
        print_input(coff_a,coff_b)

def main():
    num_rows = 10000
    num_terms = 10
    max_coof = 1000
    #gen_correct_input(num_rows,num_terms,max_coof)
    args = sys.argv[1:]
    gen_correct_output_prod(args[0])

main()


