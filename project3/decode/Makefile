TARGET = EXPAND
LIBS =
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

HEADERS = config.hpp
OBJECTS = config.cpp main.cpp

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LIBS) -o $@ -pg

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
