TARGET = project
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Wextra

HEADERS = ../../common/COMPARE.h ../../common/heap.h ../../common/bst.h ../../common/util.h
OBJECTS = ../../common/COMPARE.o ../../common/heap.o ../../common/bst.o ../../common/util.o MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) doalg.c
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f ../../common/*.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
