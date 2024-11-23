TARGET = testAlgorithms.out
SRC = algorithms.c choseAlgorithms.c fileutilsImplementation.c testAlgorithms.c
OBJ = algorithms.o choseAlgorithms.o fileutilsImplementation.o testAlgorithms.o

CFLAGS = -O3

all: $(TARGET)

# Creazione del file eseguibile
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

algorithms.o: algorithms.c algorithms.h
	gcc $(CFLAGS) -c algorithms.c

chooseAlgorithms.o: choseAlgorithms.c algorithms.h
	gcc $(CFLAGS) -c choseAlgorithms.c

fileutilsImplementation.o: fileutilsImplementation.c fileutils.h
	gcc $(CFLAGS) -c fileutilsImplementation.c

testAlgorithms.o: testAlgorithms.c algorithms.h
	gcc $(CFLAGS) -c testAlgorithms.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean