extern "C" {
    #include "f3Utils.h"
    #include "f9Utils.h"
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

static void Test_F3_Prod(benchmark::State& state){ //Testo tempo medio di un operazione.
    unsigned int size = (unsigned int)state.range(0);
    unsigned int a = 9;
    unsigned int b = 9;
    for (auto i = 0; i < size; i++){
        a *= 10;
        b *= 10;
    }

    for (auto _ : state){
        benchmark::DoNotOptimize(f3_prod(int_to_f3(a), int_to_f3(b)));
    }
}

static void Test_F9_sum(benchmark::State& state){ //Testo tempo medio di un operazione.
    unsigned int size = (unsigned int)state.range(0);
    unsigned int a_r = 9;
    unsigned int b_r = 9;
    for (auto i = 0; i < size; i++){
        a_r *= 10;
        b_r *= 10;
    }

    unsigned int a_i = 9;
    unsigned int b_i = 9;
    for (auto i = 0; i < size; i++){
        a_i *= 10;
        b_i *= 10;
    }

    for (auto _ : state){
        benchmark::DoNotOptimize(f9_sum(get_f9_element(a_i,a_r), get_f9_element(b_i,b_r)));
    }
}

static void Test_F9_prod(benchmark::State& state){ //Testo tempo medio di un operazione.
    unsigned int size = (unsigned int)state.range(0);
    unsigned int a_r = 9;
    unsigned int b_r = 9;
    for (auto i = 0; i < size; i++){
        a_r *= 10;
        b_r *= 10;
    }
    unsigned int a_i = 9;
    unsigned int b_i = 9;
    for (auto i = 0; i < size; i++){
        a_i *= 10;
        b_i *= 10;
    }

    for (auto _ : state){
        benchmark::DoNotOptimize(f9_prod(get_f9_element(a_i,a_r), get_f9_element(b_i,b_r)));
    }
}


//BENCHMARK(Test_F3_Sum)->DenseRange(1, 10, 1);
//BENCHMARK(Test_F3_Prod)->DenseRange(1, 10, 1);
BENCHMARK(Test_F9_sum)->DenseRange(1, 10, 1);
BENCHMARK(Test_F9_prod)->DenseRange(1, 10, 1);

BENCHMARK_MAIN();