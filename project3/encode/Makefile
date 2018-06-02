TARGET = LZ
LIBS =
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

HEADERS = suffix_tree.hpp queue.hpp config.hpp
OBJECTS = suffix_tree.o   queue.o   config.o   main.o

all: debug

debug: CXXFLAGS += -g
debug: $(TARGET)

release: CXXFLAGS += -O3
release: $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LIBS) -o $@ -pg

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
