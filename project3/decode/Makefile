TARGET = EXPAND
LIBS =
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

HEADERS = config.hpp
OBJECTS = config.cpp main.cpp

all: debug

debug: CXXFLAGS += -g
debug: $(TARGET)

release: CXXFLAGS += -O3
release: $(TARGET)

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LIBS) -o $@ -pg

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
