TARGET = project
LIBS =
CC = gcc
CFLAGS = -Wall -Wextra -g

HEADERS =
OBJECTS = MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) QCOUNT.c mysub.c
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@ -pg

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
	-rm -f */*.o
	-rm -f */$(TARGET)
	-rm -rf */$(TARGET).dSYM
