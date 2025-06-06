extern "C" {
    #include "f3schoolbook.h"
}

#include <stdio.h>
#include <string.h>
#include "../../benchmark/include/benchmark/benchmark.h"


static unsigned int** operands;


//./benchmarks.out --benchmark_min_warmup_time=2 --benchmark_out=output.json --benchmark_out_format=json

static void Benchmark_Schoolbook_F9(benchmark::State& state){ //Testo F9_shoolbook
    int size = static_cast<int>(state.range(0));

    f9_element* p1 = new f9_element[size];
    f9_element* p2 = new f9_element[size];

    for (int i = 0; i < size; ++i){
        p1[i] = get_f9_element(i % 3, (i * 2) % 3);
        p2[i] = get_f9_element((i * 3) % 3, (i + 1) % 3);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(schoolbook_f9(size, p1, p2));
    }
    delete[] p1;
    delete[] p2;
}

static void Benchmark_Schoolbook_F3(benchmark::State& state){ //Testo F9_shoolbook
    int size = static_cast<int>(state.range(0));

    int* p1 = new int[size];
    int* p2 = new int[size];

    for (int i = 0; i < size; ++i){
        p1[i] = (i * 2) % 3;
        p2[i] = (i * 3) % 3;
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(schoolbook_f3(size, p1, p2));
    }
    delete[] p1;
    delete[] p2;
}

//BENCHMARK(Benchmark_Schoolbook_F3)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);
BENCHMARK(Benchmark_Schoolbook_F9)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
