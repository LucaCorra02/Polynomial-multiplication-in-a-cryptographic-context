import random
import sys
import re

def open_file(file_name):
    with open(file_name, 'r') as file:
        tempi = []
        for line in file:
            match = re.search(r'\d+\.\d+', line)
            if match:
                tempi.append(float(match.group()))
    return tempi


def calc_avg(tempi):
    if len(tempi) == 0:
        return 0.0
    return sum(tempi) / len(tempi)

def main():
    args = sys.argv[1:]
    tempi = open_file(args[0])
    avg = calc_avg(tempi)
    print("Media: ",avg*1000,"ms")

    #SumBool1 = 11.002283999999996 ms
    #SumInt1 = 3.904572000000001 ms



main()