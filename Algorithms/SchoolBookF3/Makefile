TARGET = schoolbookF3.out
SRC = f3schoolbook.c f3Implementation.c
OBJ = f3schoolbook.o f3Implementation.o

CFLAGS = -O3

all: $(TARGET)

# Creazione del file eseguibile
$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: f3Implementation.c f3Utils.h
	gcc $(CFLAGS) -c f3Implementation.c

f3schoolbook.o: f3schoolbook.c
	gcc $(CFLAGS) -c f3schoolbook.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all cleanCFLAGS) -c f3Implementation.c -o f3Implementation.out