import random
import time
import sys
import numpy as np
from numpy.polynomial import Polynomial

def gen_input_f3_algo(num_terms, min_range, max_range):
    cof = np.random.randint(min_range, max_range, num_terms)
    return np.array(cof, dtype=int)

def formatted_print(p1,p2):
    st1 = ",".join([str(elem) for elem in p1])
    st2 = ",".join([str(elem) for elem in p2])
    return st1+";"+st2

def gen_intput_f9_algo(num_terms, min_range, max_range):
    c1 = np.random.randint(min_range, max_range, num_terms) + 1j * np.random.randint(min_range, max_range, num_terms)
    return np.array(c1, dtype=complex)

#Stampa nel formato parte_immaginaria:parte_reale
def formatted_print_f9(p1, p2):
    st1 = ",".join(str(int(elem.imag))+":"+str(int(elem.real)) for elem in p1)
    st2 = ",".join(str(int(elem.imag))+":"+str(int(elem.real)) for elem in p2)
    return st1+";"+st2

def gen_input_random_f3(num_rows, num_terms, min_range, max_range, file_path):
    with open(file_path, "w") as fp:
        for i in range(0, num_rows):
            p1 = gen_input_f3_algo(num_terms,min_range,max_range)
            p2 = gen_input_f3_algo(num_terms,min_range, max_range)
            s = formatted_print(p1,p2)
            fp.write(s + "\n")

def gen_input_random_f9(num_rows, num_terms, min_range, max_range, file_path):
    with open(file_path, "w") as fp:
        for i in range(0, num_rows):
            p1 = gen_intput_f9_algo(num_terms,min_range,max_range)
            p2 = gen_intput_f9_algo(num_terms,min_range, max_range)
            s = formatted_print_f9(p1,p2)
            fp.write(s + "\n")

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

def print_cof_formatted_f3(p, dim_a):
    if len(p) != 2*dim_a-1:
        diff = 2*dim_a-1 - len(p)
        for i in range(0,diff):
            p.append(0)

    str1 = ",".join([str(int(elem)) for elem in p])
    return str1

def print_cof_formatted_f9(p, dim_a):
    if len(p) != 2*dim_a-1:
        diff = 2*dim_a-1 - len(p)
        for i in range(0,diff):
            p.append((0j+0))
    str1 = ",".join(["({}i + {})".format(int(elem.imag), int(elem.real)) for elem in p])
    return str1

def gen_correct_output_prod_r(file_name):
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            a = list(map(int,tmp[0].strip().split(',')))
            b = list(map(int,tmp[1].strip().split(',')))
            p1, p2 = Polynomial(a), Polynomial(b)
            ris = p1 * p2
            print_cof_formatted_f3(ris,len(a))

def gen_correct_output_prod_f3(input_path, output_path):
    with open(input_path, "r") as file:
        with open(output_path, "w") as fp:
            for line in file:
                tmp = line.strip().split(';')
                a = list(map(int,tmp[0].strip().split(',')))
                b = list(map(int,tmp[1].strip().split(',')))
                p1, p2 = Polynomial(a), Polynomial(b)
                ris = polymod3(p1 * p2)
                ris_str = print_cof_formatted_f3(ris,len(a))
                fp.write(ris_str + "\n")

def gen_correct_output_prod_f9(input_path, output_path): #Z = (Y.real, Y.imag)
    with open(input_path, "r") as file:
        with open(output_path, "w") as fp:
            for line in file:
                tmp = line.strip().split(';')
                a = [complex(int(elem.split(':')[1]),int(elem.split(':')[0])) for elem in tmp[0].split(',')]
                b = [complex(int(elem.split(':')[1]),int(elem.split(':')[0])) for elem in tmp[1].split(',')]
                p1, p2 = Polynomial(a), Polynomial(b)
                ris = p1 * p2
                ris_str = print_cof_formatted_f9(polymod3_f9(ris),len(a))
                fp.write(ris_str + "\n")


def gen_f3(num_rows, num_terms, input_path, output_path, min_range, max_range):
    gen_input_random_f3(num_rows, num_terms, min_range, max_range, input_path)
    gen_correct_output_prod_f3(input_path, output_path)

def gen_f9(num_rows, num_terms, input_path, output_path, min_range, max_range):
    gen_input_random_f9(num_rows, num_terms, min_range, max_range, input_path)
    gen_correct_output_prod_f9(input_path, output_path)

#python3 genTestPoly num_rows num_terms f3/f9 input_path output_path
def main():
    args = sys.argv
    if len(args) < 5:
        print("Parametri richiesti: num_rows num_terms f3/f9 in/out", file=sys.stderr)
        return

    num_rows, num_terms = int(args[1]), int(args[2])
    field, input_path, output_path = args[3], args[4], args[5]
    min_range = 0
    max_range = 3

    if field == "f3":
        gen_f3(num_rows, num_terms, input_path, output_path, min_range, max_range)
    elif field == "f9":
        gen_f9(num_rows, num_terms, input_path, output_path, min_range, max_range)
    else:
        print("Campo non riconosciuti, inserisci f3 o f9", file=sys.stderr)

    ##R MAIN
    #gen_input_random_f3(num_rows, num_terms, min_range, max_range)
    #file_name = "../Karatsuba/TestFile/R/input.txt"
    #gen_correct_output_prod_r(file_name)

    ##F3 MAIN
    #gen_input_random_f3(num_rows, num_terms, min_range, max_range)
    #file_name = "TestFile/F3/input.txt"
    #gen_correct_output_prod_f3(file_name)

    ##F9 MAIN
    #gen_input_random_f9(num_rows, num_terms, min_range, max_range)
    #file_name = "TestFile/F9/input.txt"
    #gen_correct_output_prod_f9(file_name)

main()