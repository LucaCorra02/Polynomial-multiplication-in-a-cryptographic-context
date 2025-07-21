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
- [Google Benchmark](https://github.com/google/benchmark/tree/299e5928955cc62af9968370293b916f5130916f) v$1.9.3$;
- [muint](https://github.com/nemequ/munit) for Unit Test; 
- Python v3.8.10 for scripts/integration test.