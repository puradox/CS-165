TARGET = project
LIBS = -g -lm
CC = gcc
CFLAGS = -g -Wall

HEADERS = COMPARE.h heap.h util.h
OBJECTS = COMPARE.o heap.o util.o MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) doalg.c
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
