TARGET = mainTest.out
SRC = mainTest.c karatsubaField.c f9Implementation.c f3Implementation.c
OBJ = mainTest.o karatsubaField.o f9Implementation.o f3Implementation.o

CFLAGS = -O3 -Wall
F9_SRC_DIR = ../FieldImplementation

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: $(F9_SRC_DIR)/f3Implementation.c $(F9_SRC_DIR)/f3Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f3Implementation.c

f9Implementation.o: $(F9_SRC_DIR)/f9Implementation.c $(F9_SRC_DIR)/F9Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f9Implementation.c

karatsubaField.o: karatsubaField.c karatsubaField.h
	gcc $(CFLAGS) -c karatsubaField.c

mainTest.o: mainTest.c
	gcc $(CFLAGS) -c mainTest.c

benchmarks: f3schoolbook.o $(F9_SRC_DIR)/f3Implementation.o $(F9_SRC_DIR)/f9Implementation.o benchmarks.cpp #Make benchmarks compila solo i benchmarks
	g++ -c benchmarks.cpp -o benchmarks.o -I../../benchmark/include
	g++ benchmarks.o  f3schoolbook.o $(F9_SRC_DIR)/f3Implementation.o $(F9_SRC_DIR)/f9Implementation.o -std=c++11 -I. -isystem -I../../benchmark/include -L../../benchmark/build/src -lbenchmark -lpthread -o benchmarks.out

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
