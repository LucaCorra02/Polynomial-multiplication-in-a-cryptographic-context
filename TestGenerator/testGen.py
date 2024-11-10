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


def main():
    #0 -> 9 = 1
    #10 -> 99 = 2
    #100 -> 999 = 3
    #1000 -> 9999 = 4
    #10000 -> 99999 = 5
    #100000 -> 999999 = 6
    #1000000 -> 9999999 = 7 
    
    gen_input_file(1000000,0,9);
    #args = sys.argv[1:]
    #gen_correct_output_sum(args[0]);
    #gen_correct_output_prod(args[0]);

main()