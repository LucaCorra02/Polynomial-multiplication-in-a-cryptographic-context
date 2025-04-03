TARGET = mainTest.out
SRC = mainTest.c 3split.c f9Implementation.c f3Implementation.c ../../munit/munit.c
OBJ = mainTest.o 3split.o  f9Implementation.o f3Implementation.o munit.o

CFLAGS = -O3 -Wall
F9_SRC_DIR = ../FieldImplementation

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: $(F9_SRC_DIR)/f3Implementation.c $(F9_SRC_DIR)/f3Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f3Implementation.c

f9Implementation.o: $(F9_SRC_DIR)/f9Implementation.c $(F9_SRC_DIR)/F9Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f9Implementation.c

3split.o: 3split.c 3split.h
	gcc $(CFLAGS) -c 3split.c

munit.o: ../../munit/munit.c ../../munit/munit.h
	$(CC) $(CFLAGS) -c ../../munit/munit.c -o munit.o

mainTest.o: mainTest.c 3split.h ../../munit/munit.h
	gcc $(CFLAGS) -c mainTest.c

benchmarks: 3split.o $(F9_SRC_DIR)/f3Implementation.o $(F9_SRC_DIR)/f9Implementation.o benchmarks.cpp #Make benchmarks compila solo i benchmarks
	g++ -c benchmarks.cpp -o benchmarks.o -I../../benchmark/include
	g++ benchmarks.o  3split.o $(F9_SRC_DIR)/f3Implementation.o $(F9_SRC_DIR)/f9Implementation.o -std=c++11 -I. -isystem -I../../benchmark/include -L../../benchmark/build/src -lbenchmark -lpthread -o benchmarks.out

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
