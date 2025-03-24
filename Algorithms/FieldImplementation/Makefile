TARGET = mainTest.out
SRC = f3Implementation.c f9Implementation.c mainTest.c ../../munit/munit.c
OBJ = f3Implementation.o f9Implementation.o mainTest.o munit.o

CFLAGS = -O3 -Wall -I ../../munit
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: f3Implementation.c f3Utils.h
	$(CC) $(CFLAGS) -c f3Implementation.c -o f3Implementation.o

f9Implementation.o: f9Implementation.c f9Utils.h
	$(CC) $(CFLAGS) -c f9Implementation.c -o f9Implementation.o

mainTest.o: mainTest.c f3Utils.h f9Utils.h ../../munit/munit.h
	$(CC) $(CFLAGS) -c mainTest.c -o mainTest.o

munit.o: ../../munit/munit.c ../../munit/munit.h
	$(CC) $(CFLAGS) -c ../../munit/munit.c -o munit.o

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
