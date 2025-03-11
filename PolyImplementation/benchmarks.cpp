extern "C" {
    #include "f3Utils.h"
    #include "utils.h"
}
#include <benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>

static unsigned int** operands;
static std::string PATH = "../TestFile/Cifra4/input.txt";
static const unsigned int num_operators = 2;
static const unsigned int num_operations = 1000000;

static void DoSetup(const benchmark::State& state) {
    operands= create_vector(num_operations,num_operators);
    read_file((char*)PATH.c_str(), num_operations, operands);
}

static void TearDown() {
    free_vector(operands,num_operations);
}

static void BM_TestBench(benchmark::State& state) {
    int ris = f3_sum(10, 10);
    //printf("ris = %d\n", ris);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(f3_sum(0, 2));
    }
}

BENCHMARK(BM_TestBench)->Setup(DoSetup);

BENCHMARK_MAIN();