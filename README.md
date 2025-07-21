# Polynomial Multiplication over $\mathbb{F}_3$

This repository provides implementations of recursive polynomial multiplication algorithms over the finite field $\mathbb{F}_3$. 
These algorithms are designed to work with polynomials of an arbitrary number of terms.
For each algorithm, there are $3$ different types of implementations:
- Single-thread classic;
- Single-thread hybrid (DP);
- Multi-thread.

Specifically, the algorithms implemented are:
- Schoolbook;
- Karatsuba (Bernstein version);
- 3-Split (in two versions)
- 4-Split (in two versions)
- 5-Split

The repository also includes benchmarking and testing tool.

## Prerequisites
- C, C++17;
- CMake $\geq 3.14$;
- GCC v13.1.0. For $\texttt{-O3}$ optimization and for $\texttt{OpenMp}$ support;
- [Google Benchmark](https://github.com/google/benchmark/tree/299e5928955cc62af9968370293b916f5130916f) v1.9.3;
- [muint](https://github.com/nemequ/munit) for Unit Test; 
- Python v3.8.10 for scripts/integration test.

for setup google benchmark: 
```sh
# On the root of the repo
$ git submodule update --init --recursive
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ cmake -E make_directory "build"
# Generate build system files with cmake, and download any dependencies.
$ cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
# Build the library.
$ cmake --build "build" --config Release 
```

## Field implementation
The directory `Algorithms/FieldImplementation` contains the representations of the fields $\mathbb{F}_3$ and $\mathbb{F}_9$.

The file `Algorithms/algoUtils.h` defines the polynomial operations used by the algorithms.

## Single-Thread Base

The implementation using a classical recursive logic is located in the `Algorithms` directory.
The function signatures of all algorithms are defined in the `Algorithms/algorithms.h` header file.

To compile the code, run:
```bash
#For main
make all
#For benchmark
make benchmarks
```
The executable  `./mainTest.out` is used to test the algorithms, while `./benchmarks.out` is used to measure their performance.

## Single-Thread Hybrid

The directory `Algorithms/HybridAlgo` contains the implementation that uses a hybrid logic, where different algorithms are dynamically combined.

The script `createTree.py` generates an optimized computation tree using a dynamic programming approach based on the benchmark resukts. The selected algorithm IDs are saved into the files `f9_min.txt` and `f3_min.txt`.
The script must be executed first for `f9` and then for `f3`, as shown below:

```bash
python3 createTree.py f9 max_degree_poly > log_f9.txt 2>&1
python3 createTree.py f3 max_degree_poly > log_f3.txt 2>&1
```
Here, `max_degree_poly` is the maximum degree up to which the optimized tree should be generated.

To compile the code, run:
```bash
#For main
make all
#For benchmark
make benchmarks
```
The executable  `./mainTest.out` is used to test the algorithms, while `./benchmarks.out` is used to measure their performance.

## Multi-Thread

This implementation uses OpenMP directives to parallelize the recursive function calls.  
It is located in the `MultiThread` branch, inside the `Algorithms` directory.
For optimal performance, it may be necessary to set a maximum number of threads using the environment variable:

```bash
export OMP_NUM_THREADS=8
```
To compile the code, run:
```bash
git checkout MultiThread
# For main
make all
# For benchmark
make benchmarks
```
## Test

### Unit Tests

To run the unit tests, the following functions must be called from the `./mainTest.c` file:

```c
munit_suite_main(&suite, NULL, argc, argv);
munit_suite_main(&suite_f3, NULL, argc, argv);
```
After execution, the test runner will indicate whether each test has passed or failed.

### Unit Tests
Integration tests rely on the `Poly` module from the `NumPy` library and require random polynomial inputs.
To generate them, use the script `Algorithms/genTestPoly.py`:
```bash
python3 genTestPoly.py num_rows num_terms f3/f9 input.txt correct_output.txt
```
where: 
- `num_rows` is the number of input/output pairs to generate;
- `num_terms` is the number of terms of the input polynomials $a(x), b(x)$.
Then, to test the algorithms using the generated inputs:
```bash
./mainTest.out --field=f3/f9 --degree=num_terms < input.txt > out.txt
diff --color correct_output.txt out.txt
```
This will compare the expected and actual output, highlighting any differences.

## Benchmark

To measure the performance of a specific algorithm, you can use the following command:

```bash
  ./benchmarks.out --algo=algoname_f3 --degree=num_terms --benchmark_min_warmup_time=2 --benchmark_out=out.json --benchmark_out_format=json
```
This command benchmarks the time required to compute the product of two polynomials with `num_terms` terms.
The available algorithms for the $\mathbb{F}_3$ field are:
- schoolbook_f3;
- karatsuba_f3;
- split_3_f3;
- split_3_v2_f3;
- split_4_v1_f3;
- split_4_v2_f3;
- split_5_f3.

Same for $\mathbb{F}_9$ field.