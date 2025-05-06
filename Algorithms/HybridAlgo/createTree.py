import subprocess
import os
import re
import json
import sys
from operator import itemgetter

f3_algo = {"schoolbook_f3":1, "karatsuba_f3":1, "split_3_f3":6, "split_3_v2_f3":6, "split_4_v1_f3":18, "split_4_v2_f3":18, "split_5_f3":32}
f9_algo = {"schoolbook_f9":1, "karatsuba_f9":1, "split_3_f9":6, "split_3_v2_f9":6, "split_4_v1_f9":18, "split_4_v2_f9":18, "split_5_f9":32}

def execute_benchmark(algo, degree):
    comand = "./benchmarks.out --algo={algo_name} --degree={deg} --benchmark_min_warmup_time=0 --benchmark_format=json --benchmark_repetitions=3".format(algo_name = algo, deg=degree)
    s = subprocess.check_output(comand, shell=True)
    parsed = json.loads(s)['benchmarks'][3]
    return float(parsed['real_time'])

def write_best_algo(algo_id, file_name):
    with open(file_name, "a") as file:
        file.write(str(algo_id) + "\n")

def benchmark_degree_x_f3(degree):
    times = {}
    print("Degree: ", degree)
    for algo_name, min_degree in f3_algo:
        if degree < min_degree:
            continue
        time = execute_benchmark(algo_name,degree)
        times[algo_name] = time
    print(times)
    min_algo = min(list(times.items()), key=itemgetter(1))
    print("min: ", min_algo)
    return list(f3_algo).index(min_algo[0])

def benchmark_degree_x_f9(degree):
    times = {}
    print("Degree: ", degree)

    for algo_name, min_degree in f9_algo.items():
        if degree < min_degree:
            continue
        time = execute_benchmark(algo_name,degree)
        times[algo_name] = time
    print(times)
    min_algo = min(list(times.items()), key=itemgetter(1))
    print("min: ", min_algo)
    print("Deg: ",degree,"Algo: ",min_algo, file=sys.stderr)
    return list(f9_algo).index(min_algo[0])

#Partire con file 0 a capo
with open("f9_min.txt", "w") as file:
    file.write(str(0) + "\n")
for i in range(1,762):
    min_algo_id = benchmark_degree_x_f9(i)
    write_best_algo(min_algo_id, "f9_min.txt")


