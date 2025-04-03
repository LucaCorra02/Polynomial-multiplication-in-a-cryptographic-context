import random
import time

import numpy as np
from numpy.polynomial import Polynomial

def gen_input_f3_algo(num_terms, min_range, max_range):
    cof = np.random.randint(min_range, max_range, num_terms)
    return np.array(cof, dtype=int)

def formatted_print(p1,p2):
    st1 = ",".join([str(elem) for elem in p1])
    st2 = ",".join([str(elem) for elem in p2])
    print(st1,st2,sep=";")

def gen_intput_f9_algo(num_terms, min_range, max_range):
    c1 = np.random.randint(min_range, max_range, num_terms) + 1j * np.random.randint(min_range, max_range, num_terms)
    return np.array(c1, dtype=complex)

#Stampa nel formato parte_immaginaria:parte_reale
def formatted_print_f9(p1, p2):
    st1 = ",".join(str(int(elem.imag))+":"+str(int(elem.real)) for elem in p1)
    st2 = ",".join(str(int(elem.imag))+":"+str(int(elem.real)) for elem in p2)
    print(st1,st2,sep=";")

def gen_input_random_f3(num_rows, num_terms, min_range, max_range):
    for i in range(0, num_rows):
        p1 = gen_input_f3_algo(num_terms,min_range,max_range)
        p2 = gen_input_f3_algo(num_terms,min_range, max_range)
        formatted_print(p1,p2)

def gen_input_random_f9(num_rows, num_terms, min_range, max_range):
    for i in range(0, num_rows):
        p1 = gen_intput_f9_algo(num_terms,min_range,max_range)
        p2 = gen_intput_f9_algo(num_terms,min_range, max_range)
        formatted_print_f9(p1,p2)

def polymod3(ris):
    ris_mod3 = []
    for cof in ris.coef:
        ris_mod3.append(int(cof)%3)
    return ris_mod3

def polymod3_f9(ris):
    ris_mod3 = []
    for cof in ris.coef:
        ris_mod3.append(complex(cof.real%3,cof.imag%3))
    return ris_mod3

def print_cof_formatted(p):
    st1 = ",".join([str(int(elem)) for elem in p])
    print(st1)

def print_cof_formatted_f9(p):
    str = ",".join(["({}i + {})".format(int(elem.imag), int(elem.real)) for elem in p])
    print(str)

def gen_correct_output_prod_r(file_name):
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            a = list(map(int,tmp[0].strip().split(',')))
            b = list(map(int,tmp[1].strip().split(',')))
            p1, p2 = Polynomial(a), Polynomial(b)
            ris = p1 * p2
            print_cof_formatted(ris)

def gen_correct_output_prod_f3(file_name):
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            a = list(map(int,tmp[0].strip().split(',')))
            b = list(map(int,tmp[1].strip().split(',')))
            p1, p2 = Polynomial(a), Polynomial(b)
            ris = polymod3(p1 * p2)
            print_cof_formatted(ris)

def gen_correct_output_prod_f9(file_name): #Z = (Y.real, Y.imag)
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            a = [complex(int(elem.split(':')[1]),int(elem.split(':')[0])) for elem in tmp[0].split(',')]
            b = [complex(int(elem.split(':')[1]),int(elem.split(':')[0])) for elem in tmp[1].split(',')]
            p1, p2 = Polynomial(a), Polynomial(b)
            ris = p1 * p2
            print_cof_formatted_f9(polymod3_f9(ris))


def main():
    num_rows = 100
    num_terms = 133
    min_range = 1
    max_range = 100

    ##R MAIN
    #gen_input_random_f3(num_rows, num_terms, min_range, max_range)
    #file_name = "../Karatsuba/TestFile/R/input.txt"
    #gen_correct_output_prod_r(file_name)

    ##F3 MAIN
    #gen_input_random_f3(num_rows, num_terms, min_range, max_range)
    #file_name = "../Karatsuba/TestFile/F3/input.txt"
    #gen_correct_output_prod_f3(file_name)

    ##F9 MAIN
    #gen_input_random_f9(num_rows, num_terms, min_range, max_range)
    file_name = "Karatsuba/TestFile/F9/input.txt"
    gen_correct_output_prod_f9(file_name)

main()