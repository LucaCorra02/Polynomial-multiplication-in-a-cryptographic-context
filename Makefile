TARGET = f9Operation.out #Nome File Eseguibile
SRC = f3Implementation.c f9Operation.c
OBJ = f3Implementation.o f9Operation.o

CFLAGS = -O3

all: clean $(TARGET)
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: f3Implementation.c # Compila f3Implementation.c in f3Implementation.o
	gcc -c f3Implementation.c

f9Operation.o: f9Operation.c
	gcc -c f9Operation.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean