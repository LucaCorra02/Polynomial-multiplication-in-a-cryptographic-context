import subprocess
import os
import re
import json


f3_algo = ["schoolbook_f3", "karatsuba_f3", "split_3_f3", "split_3_v2_f3", "split_4_v1_f3", "split_4_v2_f3", "split_5_f3"]

def execute_benchmark_f3(algo, degree):
    comand = "./benchmarks.out --algo={algo_name} --degree={deg} --benchmark_min_warmup_time=2 --benchmark_format=json".format(algo_name = algo, deg=degree)
    s = subprocess.check_output(comand, shell=True)
    parsed = json.loads(s)['benchmarks'][0]
    return float(parsed['real_time'])

def benchmark_degree_x(degree):
    for algo_name in f3_algo:
        time = execute_benchmark_f3(algo_name,degree)
        print(f"Algo: {algo_name}, Degree: {degree}, Time: {time}")



benchmark_degree_x(1024)