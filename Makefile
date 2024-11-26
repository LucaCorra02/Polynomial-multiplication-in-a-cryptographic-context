TARGET = mainOperation.out #Nome File Eseguibile
SRC = f3Implementation.c f9Operation.c mainOperation.c
OBJ = f3Implementation.o f9Operation.o mainOperation.o

CFLAGS = -O3

all: clean $(TARGET)
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: f3Implementation.c # Compila f3Implementation.c in f3Implementation.o
	gcc $(CFLAGS) -c f3Implementation.c

f9Operation.o: f9Operation.c
	gcc $(CFLAGS) -c f9Operation.c

mainOperation.o: mainOperation.c getTime.h
	gcc $(CFLAGS) -c mainOperation.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean