extern "C" {
    #include "3split.h"
}

#include <stdio.h>
#include <string.h>
#include "../../benchmark/include/benchmark/benchmark.h"

//./benchmarks.out --benchmark_min_warmup_time=20s

static void Benchmark_3split_v2_f9(benchmark::State& state){ //Testo F9_split3
    int size = static_cast<int>(state.range(0));

    f9_element* p1 = new f9_element[size];
    f9_element* p2 = new f9_element[size];

    for (int i = 0; i < size; ++i){
        p1[i] = get_f9_element(i % 3, (i * 2) % 3);
        p2[i] = get_f9_element((i * 3) % 3, (i + 1) % 3);
    }

    for (auto _ : state) {
        (split_3_v2_f9(size, p1, p2));
    }
    delete[] p1;
    delete[] p2;
}



BENCHMARK(Benchmark_3split_v2_f9)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);
//BENCHMARK(Benchmark_3split_f3)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
