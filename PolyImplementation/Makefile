TARGET = mainOperation.out #Nome File Eseguibile
SRC = f3Implementation.c f9Operation.c benchmarkImplementation.c utilsImplementation.c mainOperation.c
OBJ = f3Implementation.o f9Operation.o benchmarkImplementation.o utilsImplementation.o mainOperation.o

CFLAGS = -O3 -flto

all: clean $(TARGET)
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: f3Implementation.c # Compila f3Implementation.c in f3Implementation.o
	gcc $(CFLAGS) -c f3Implementation.c

f9Operation.o: f9Operation.c
	gcc $(CFLAGS) -c f9Operation.c

benchmarkImplementation.o : benchmarkImplementation.c getTime.h f9Utils.h f9Benchmark.h
	gcc $(CFLAGS) -c benchmarkImplementation.c

utilsImplementation.o :
	gcc $(CFLAGS) -c utilsImplementation.c

mainOperation.o: mainOperation.c getTime.h
	gcc $(CFLAGS) -c mainOperation.c

benchmarks: utilsImplementation.o benchmarkImplementation.o f9Operation.o f3Implementation.o benchmarks.cpp #Make benchmarks compila solo i benchmarks
	g++ -c benchmarks.cpp -o benchmarks.o -I./../benchmark/include
	g++ benchmarks.o utilsImplementation.o benchmarkImplementation.o f9Operation.o f3Implementation.o -std=c++11 -I. -isystem -I../benchmark/include -L../benchmark/build/src -lbenchmark -lpthread -o benchmarks.out

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean