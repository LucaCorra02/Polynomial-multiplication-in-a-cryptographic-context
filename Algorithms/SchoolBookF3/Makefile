TARGET = f3schoolbook.out
SRC = f3schoolbook.c f9Implementation.c f3Implementation.c
OBJ = f3schoolbook.o f9Implementation.o f3Implementation.o

CFLAGS = -O3 -Wall
SRC_DIR = ../FieldImplementation # Directory per i file di implementazione di f9 e f3

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: $(SRC_DIR)/f3Implementation.c f3Utils.h
	gcc $(CFLAGS) -c $(SRC_DIR)/f3Implementation.c

f9Implementation.o: $(SRC_DIR)/f9Implementation.c $(SRC_DIR)/F9Utils.h
	gcc $(CFLAGS) -c $(SRC_DIR)/f9Implementation.c

f3schoolbook.o: f3schoolbook.c
	gcc $(CFLAGS) -c f3schoolbook.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean