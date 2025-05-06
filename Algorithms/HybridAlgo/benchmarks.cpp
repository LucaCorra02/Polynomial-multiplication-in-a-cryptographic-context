extern "C" {
#include "algorithms.h"
}

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <x86intrin.h>  // Per __rdtsc()
#include "../../benchmark/include/benchmark/benchmark.h"


//./benchmarks.out --benchmark_min_warmup_time=2 --benchmark_out=File/3splitf3.json --benchmark_out_format=json

static void Benchmark_4split_v2_f9(benchmark::State& state){ //Testo F9_split3
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

static void Benchmark_cpu_cycle_f9(benchmark::State& state) {
    int size = static_cast<int>(state.range(0));

    f9_element* p1 = new f9_element[size];
    f9_element* p2 = new f9_element[size];

    for (int i = 0; i < size; ++i) {
        p1[i] = get_f9_element(i % 3, (i * 2) % 3);
        p2[i] = get_f9_element((i * 3) % 3, (i + 1) % 3);
    }

    unsigned long long total_cycles = 0;
    const int inner_loops = 100;

    for (auto _ : state) {
        unsigned long long start = __rdtsc();
        for (int j = 0; j < inner_loops; ++j) {
            benchmark::DoNotOptimize(split_4_f9(size, p1, p2));
        }
        unsigned long long end = __rdtsc();
        total_cycles += (end - start);
    }

    delete[] p1;
    delete[] p2;

    double avg_cycles = static_cast<double>(total_cycles) / (state.iterations() * inner_loops);
    state.counters["AvgCycles"] = benchmark::Counter(avg_cycles);
}


static void Benchmark_4split_f3(benchmark::State& state){
    int size = static_cast<int>(state.range(0));

    int* p1 = new int[size];
    int* p2 = new int[size];

    for (int i = 0; i < size; ++i){
        p1[i] = (i + 1) % 3;
        p2[i] = (i * 3) % 3;
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(split_4_f3(size, p1, p2));
    }
    delete[] p1;
    delete[] p2;
}

//./benchmarks.out --algo=split_3_f3 --degree=761  --benchmark_min_warmup_time=2 --benchmark_out=split_3_f3.json --benchmark_out_format=json

std::string selected_algo = "";
int selected_degree = -1;

using AlgoFn_f3 = int* (*)(int, int*, int*);
std::map<std::string, AlgoFn_f3> algo_map_f3 = {
    {"schoolbook_f3", schoolbook_f3},
    {"karatsuba_f3", unbalanced_karatsuba_f3},
    {"split_3_f3", split_3_f3},
    {"split_3_v2_f3", split_3_v2_f3},
    {"split_4_v1_f3", split_4_v1_f3},
    {"split_4_v2_f3", split_4_f3},
    {"split_5_f3", split_5_f3}
};

static void BenchmarkF3(benchmark::State& state) {
    int size = static_cast<int>(state.range(0));
    int* p1 = new int[size];
    int* p2 = new int[size];

    for (int i = 0; i < size; ++i){
        p1[i] = (i + 1) % 3;
        p2[i] = (i * 3) % 3;
    }

    auto it = algo_map_f3.find(selected_algo);
    if (it == algo_map_f3.end()) {
        std::cerr << "Algoritmo non riconosciuto: " << selected_algo << std::endl;
        delete[] p1;
        delete[] p2;
        return;
    }

    AlgoFn_f3 selected_fn = it->second;
    int* result = nullptr;
    for (auto _ : state) {
        result = selected_fn(size, p1, p2);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
        delete[] result;
    }

    delete[] p1;
    delete[] p2;
}

using AlgoFn_f9 = f9_element* (*)(int, f9_element*, f9_element*);
std::map<std::string, AlgoFn_f9> algo_map_f9 = {
    {"schoolbook_f9", schoolbook_f9},
    {"karatsuba_f9", unbalanced_karatsuba_f9},
    {"split_3_f9", split_3_f9},
    {"split_3_v2_f9", split_3_v2_f9},
    {"split_4_v1_f9", split_4_v1_f9},
    {"split_4_v2_f9", split_4_f9},
    {"split_5_f9", split_5_f9}
};

static void BenchmarkF9(benchmark::State& state) {
    int size = static_cast<int>(state.range(0));

    f9_element* p1 = new f9_element[size];
    f9_element* p2 = new f9_element[size];
    for (int i = 0; i < size; ++i) {
        p1[i] = get_f9_element(i % 3, (i * 2) % 3);
        p2[i] = get_f9_element((i * 3) % 3, (i + 1) % 3);
    }

    read_file_f9("f9_min.txt", size);
    auto it = algo_map_f9.find(selected_algo);
    if (it == algo_map_f9.end()) {
        std::cerr << "Algoritmo non riconosciuto: " << selected_algo << std::endl;
        delete[] p1;
        delete[] p2;
        return;
    }

    AlgoFn_f9 selected_fn = it->second;
    f9_element* result = nullptr;
    for (auto _ : state) {
        result = selected_fn(size, p1, p2);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
        delete[] result;
    }
    delete[] p1;
    delete[] p2;
}

//BENCHMARK(BenchmarkF9)->DenseRange(30, 400, 10)->Unit(benchmark::kMillisecond);
//BENCHMARK(BenchmarkF3)->DenseRange(761,761,1)->Unit(benchmark::kMillisecond);

//BENCHMARK(Benchmark_4split_v2_f9)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);
//BENCHMARK(Benchmark_4split_f3)->DenseRange(10, 3048, 100)->Unit(benchmark::kMillisecond);
//BENCHMARK_MAIN();


int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--algo=", 0) == 0) {
            selected_algo = arg.substr(7);
        } else if (arg.rfind("--degree=", 0) == 0) {
            selected_degree = std::stoi(arg.substr(9));
        }
    }

    if (selected_algo.empty()) {
        std::cerr << "Errore: specificare l'algoritmo con --algo=nome_algoritmo" << std::endl;
        return 1;
    }
    if (selected_degree < 1) {
        std::cerr << "Errore: specificare il grado con --degree=numero" << std::endl;
        return 1;
    }

    ::benchmark::Initialize(&argc, argv);
    benchmark::RegisterBenchmark("BenchmarkF9", BenchmarkF9)
        ->Arg(selected_degree)
        ->Unit(benchmark::kMillisecond);

    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}