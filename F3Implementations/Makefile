TARGET = mainTest.out #Nome File Eseguibile
SRC = basicOperation.c benchmarkImplementation.c mainTest.c
OBJ = basicOperation.o benchmarkImplementation.o mainTest.o

CFLAGS = -O3 -flto

all: clean $(TARGET)
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

basicOperation.o: basicOperation.c f3bits.h # Compila f3Implementation.c in f3Implementation.o
	gcc $(CFLAGS) -c basicOperation.c

benchmarkImplementation.o: benchmarkImplementation.c benchmark.h
	gcc $(CFLAGS) -c benchmarkImplementation.c

mainTest.o: mainTest.c benchmark.h benchmark.h f3bits.h
	gcc $(CFLAGS) -c mainTest.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean