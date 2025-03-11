extern "C" {
    #include "f3Utils.h"
}
#include <benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>

static unsigned int** operands;
static std::string PATH = "../TestFile/Cifra4/input.txt";
static const unsigned int num_operators = 2;
static const unsigned int num_operations = 1000000;

//./benchmarks.out --benchmark_min_warmup_time 20s

static void Test_F3_Sum(benchmark::State& state){ //Testo tempo medio di un operazione.
    unsigned int size = (unsigned int)state.range(0);
    unsigned int a = 9;
    unsigned int b = 9;
    for (auto i = 0; i < size; i++){
        a *= 10;
        b *= 10;
    }

    for (auto _ : state){
        benchmark::DoNotOptimize(f3_sum(int_to_f3(a), int_to_f3(b)));
    }
}

BENCHMARK(Test_F3_Sum)->DenseRange(1, 10, 1);

BENCHMARK_MAIN();