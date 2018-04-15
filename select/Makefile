TARGET = project
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Wextra -Weverything

HEADERS = COMPARE.h heap.h util.h
OBJECTS = COMPARE.o heap.o util.o MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) doalg.c
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
