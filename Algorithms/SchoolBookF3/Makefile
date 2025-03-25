TARGET = f3schoolbook.out
SRC = f3schoolbook.c f9Implementation.c f3Implementation.c
OBJ = f3schoolbook.o f9Implementation.o f3Implementation.o

CFLAGS = -O3 -Wall
F9_SRC_DIR = ../FieldImplementation

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(TARGET)

f3Implementation.o: $(F9_SRC_DIR)/f3Implementation.c $(F9_SRC_DIR)/f3Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f3Implementation.c

f9Implementation.o: $(F9_SRC_DIR)/f9Implementation.c $(F9_SRC_DIR)/F9Utils.h
	gcc $(CFLAGS) -c $(F9_SRC_DIR)/f9Implementation.c

f3schoolbook.o: f3schoolbook.c
	gcc $(CFLAGS) -c f3schoolbook.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
