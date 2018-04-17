TARGET = project
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Wextra

HEADERS =
OBJECTS = MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) doalg.c
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
	-rm -f */*.o
	-rm -f */$(TARGET)
	-rm -rf */$(TARGET).dSYM
