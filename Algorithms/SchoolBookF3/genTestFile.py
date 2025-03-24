import random
import numpy as np

def gen_input_f3_algo(num_terms, min_range, max_range):
    p1 = []
    for _ in range(num_terms):

        num = random.randint(min_range, max_range)
        p1.append(num)
    return p1

def gen_input_random(num_rows, num_terms, min_range, max_range):
    for i in range(0,num_rows):
        p1 = gen_input_f3_algo(num_terms,min_range,max_range)
        p2 = gen_input_f3_algo(num_terms,min_range, max_range)
        formatted_print(p1,p2)

def polymod3(ris):
    ris_mod3 = []
    for cof in ris:
        ris_mod3.append(cof%3)
    return ris_mod3

def print_cof_formatted(p):
    st1 = ",".join([str(elem) for elem in p])
    print(st1)

def gen_correct_output_prod(file_name):
    with open(file_name, "r") as file:
        for line in file:
            tmp = line.strip().split(';')
            a = list(map(int,tmp[0].strip().split(',')))
            b = list(map(int,tmp[1].strip().split(',')))
            p1, p2 = np.poly1d(a), np.poly1d(b)
            ris = polymod3(np.polymul(p1,p2))
            print_cof_formatted(ris)


def formatted_print(p1,p2):
    st1 = ",".join([str(elem) for elem in p1])
    st2 = ",".join([str(elem) for elem in p2])
    print(st1,st2,sep=";")

def main():
    num_rows = 100
    num_terms = 1024
    min_range = 0
    max_range = 1000
    #gen_input_random(num_rows, num_terms, min_range, max_range)
    file_name = "TestFile/input1.txt"
    gen_correct_output_prod(file_name)

main()