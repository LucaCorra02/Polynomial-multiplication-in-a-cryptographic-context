CFLAGS = -O3 -flto

all: benchmarks.out

f3UtilsImplementation.o: f3UtilsImplementation.c f3Utils.h
	gcc $(CFLAGS) -c f3UtilsImplementation.c -o f3UtilsImplementation.o

basicOperation.o: basicOperation.c f3bits.h f3Utils.h
	gcc $(CFLAGS) -c basicOperation.c -o basicOperation.o

basicOperationBool.o: basicOperationBool.c f3bool.h f3Utils.h
	gcc $(CFLAGS) -c basicOperationBool.c -o basicOperationBool.o

benchmarks.o: benchmarks.cpp
	g++ -c benchmarks.cpp -o benchmarks.o -I./../benchmark/include

benchmarks.out: basicOperation.o basicOperationBool.o f3UtilsImplementation.o benchmarks.o
	g++ benchmarks.o basicOperation.o basicOperationBool.o f3UtilsImplementation.o -std=c++11 -I. -isystem -I../benchmark/include -L../benchmark/build/src -lbenchmark -lpthread -o benchmarks.out
clean:
	rm -f *.o benchmarks.out