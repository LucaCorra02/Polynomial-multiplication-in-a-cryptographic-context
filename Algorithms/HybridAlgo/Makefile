TARGET = mainTest.out
SRC = mainTest.c algorithms.c algoUtils.c f9Implementation.c f3Implementation.c ../munit/munit.c
OBJ = mainTest.o algorithms.o algoUtils.o f9Implementation.o f3Implementation.o munit.o

CFLAGS = -O3 -Wall -fopenmp
F9_SRC_DIR = ../FieldImplementation
ALGO_UTILS_SRC_DIR = ..

#./benchmarks.out --benchmark_out=ris.json --benchmark_out_format=json --benchmark_min_warmup_time=2

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: $(F9_SRC_DIR)/f3Implementation.c $(F9_SRC_DIR)/f3Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f3Implementation.c

f9Implementation.o: $(F9_SRC_DIR)/f9Implementation.c $(F9_SRC_DIR)/F9Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f9Implementation.c

algoUtils.o: $(ALGO_UTILS_SRC_DIR)/algoUtils.c $(ALGO_UTILS_SRC_DIR)/algorithms.h
	gcc $(CFLAGS) -c $(ALGO_UTILS_SRC_DIR)/algoUtils.c

munit.o: ../../munit/munit.c ../../munit/munit.h
	$(CC) $(CFLAGS) -c ../../munit/munit.c -o munit.o

algorithms.o: algorithms.c algorithms.h
	gcc $(CFLAGS) -c algorithms.c

mainTest.o: mainTest.c algorithms.h ../../munit/munit.h
	gcc $(CFLAGS) -c mainTest.c

benchmarks: algorithms.o algoUtils.o f3Implementation.o f9Implementation.o benchmarks.cpp
	g++ $(CFLAGS) -c benchmarks.cpp -o benchmarks.o -I../../benchmark/include
	g++ $(CFLAGS) benchmarks.o algorithms.o algoUtils.o f3Implementation.o f9Implementation.o \
		-std=c++14 -I. -isystem -I../../benchmark/include -L../../benchmark/build/src -lbenchmark -lpthread -o benchmarks.out

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
