import subprocess
import os
import json

def execute_benchmark_f3(algo):
    comand = "./benchmarks.out --algo={algo_name} --benchmark_min_warmup_time=2 --benchmark_format=json".format(algo_name = algo)
    s = subprocess.check_output(comand, shell=True)
    parsed = json.loads(s)
    print(parsed['benchmarks'])


time = execute_benchmark_f3("schoolbook_f3")
print(time)