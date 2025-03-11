extern "C" {
    #include "f3bool.h"
    #include "f3bits.h"
    #include "f3Utils.h"
}
#include <benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>

static void VBITS_SUM_TEST(benchmark::State& state) {
    unsigned int size = (unsigned int)state.range(0);
    unsigned int a = 2;
    unsigned int b = 9;
    for (auto i = 0; i < size; i++){a *= 10, b *= 10;}
    //int ris = f3_sum(int_to_F3(a),int_to_F3(b));
    //printf("a: %d, b: %d, ris: %d\n",a,b,ris);
    for (auto _ : state){
        benchmark::DoNotOptimize(f3_sum(int_to_F3(a),int_to_F3(b)));
    }

}

BENCHMARK(VBITS_SUM_TEST)->DenseRange(0, 8, 1);

BENCHMARK_MAIN();