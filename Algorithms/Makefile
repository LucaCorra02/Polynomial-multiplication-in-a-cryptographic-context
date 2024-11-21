TARGET = testAlgorithms.out
SRC = algorithms.c choseAlgorithms.c testAlgorithms.c
OBJ = algorithms.o choseAlgorithms.o testAlgorithms.o

CFLAGS = -O3

all: $(TARGET)

# Creazione del file eseguibile
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

algorithms.o: algorithms.c algorithms.h
	gcc $(CFLAGS) -c algorithms.c

chooseAlgorithms.o: choseAlgorithms.c algorithms.h
	gcc $(CFLAGS) -c choseAlgorithms.c

testAlgorithms.o: testAlgorithms.c algorithms.h
	gcc $(CFLAGS) -c testAlgorithms.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean