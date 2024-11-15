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
    #ProdBool1 = 8.900487999999996 ms
    #SumInt1 = 3.904572000000001 ms
    #ProdInt1 = 3.239713999999997 ms


    #SumBool2 Media:  12.462761999999987 ms
    #ProdBool2 Media:  12.002687999999992 ms
    #SumInt2 = Media:  4.530682000000002 ms
    #ProdInt2 = Media:  4.0223739999999975 ms


    #SumBool3 = Media:  12.551346000000013 ms
    #ProdBool3 = Media:  12.116530000000013 ms
    #SumInt3 = Media:  4.2429960000000015 ms
    #ProdInt3 = Media:  4.090098000000002 ms


    #F9PROD_POSITIVO = Media:  147.27714999999995 ms
    #F9PROD_IMG_NEG = Media:  226.22134000000005 ms
    #F9PROD_NEG Media:  196.22944000000004 ms

main()