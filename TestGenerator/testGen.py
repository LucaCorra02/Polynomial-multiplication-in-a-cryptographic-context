import random
import sys

def gen_correct_output_sum(file_name):
    with open(file_name, "r") as file:
        for line in file:
            a, b = map(int, line.strip().split(','))
            somma = (a + b)%3
            print(somma)

def gen_correct_output_prod(file_name):
    with open(file_name, "r") as file:
        for line in file:
            a, b = map(int, line.strip().split(','))
            somma = (a * b)%3
            print(somma)

def gen_input_file(size, min_range ,max_range):
    for _ in range(size):
        a = random.randint(min_range, max_range)
        b = random.randint(min_range, max_range)
        print("%d,%d"%(a,b)) 

def gen_input_f9(size, min_range, max_range):
    for _ in range(size):
        a_img = random.randint(min_range, max_range)
        a_real = random.randint(min_range, max_range)
        b_img = random.randint(min_range, max_range)
        b_real = random.randint(min_range, max_range)
        print("%d,%d;%d,%d"%(a_img,a_real,b_img,b_real))

def gen_correct_output_f9prod(file_name):
    with open(file_name, "r") as file:
        for line in file:
            ops = line.split(";")
            a_img, a_real = map(int, ops[0].split(','))
            b_img, b_real = map(int, ops[1].split(','))

            ris_img = ((a_real * b_img) + (a_img * b_real))%3
            ris_real = ((a_real * b_real) - (a_img * b_img))%3
            print("%dw + %d"%(ris_img,ris_real))

def main():
    #0 -> 9 = 1
    #10 -> 99 = 2
    #100 -> 999 = 3
    #1000 -> 9999 = 4
    #10000 -> 99999 = 5
    #100000 -> 999999 = 6
    #1000000 -> 9999999 = 7 
    
    #gen_input_file(1000000,100,999);
    args = sys.argv[1:]
    #gen_correct_output_sum(args[0]);
    #gen_correct_output_prod(args[0]);
    #gen_input_f9(1000000,-100,1000);
    gen_correct_output_f9prod(args[0]);


main()


