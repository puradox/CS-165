TARGET = project
LIBS =
CC = gcc-7
CFLAGS = -Wall -Wextra -g

HEADERS = perf.h triplet.h find.h mysub.h
OBJECTS = perf.c triplet.c find.c mysub.c MAIN.c

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@ -pg

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
	-rm -f */*.o
	-rm -f */$(TARGET)
	-rm -rf */$(TARGET).dSYM
