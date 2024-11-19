TARGET = Schoolbook/schoolbook.out #Nome File Eseguibile
SRC = fileutilsImplementation.c Schoolbook/schoolbook.c
OBJ = fileutilsImplementation.o Schoolbook/schoolbook.o

CFLAGS = -O3

all: clean $(TARGET)
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: fileutilsImplementation.c # Compila f3Implementation.c in f3Implementation.o
	gcc $(CFLAGS) -c fileutilsImplementation.c

f9Operation.o: Schoolbook
	gcc $(CFLAGS) -c Schoolbook/schoolbook.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean