TARGET = EXPAND.exe
LIBS =
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

HEADERS = config.hpp interpreter.hpp lookback.hpp
OBJECTS = config.o   interpreter.o   lookback.o

TEST_TARGET  = test.exe
TEST_HEADERS = catch.hpp
TEST_OBJECTS = catch.o   interpreter_tests.o

.PHONY: all
all: debug

.PHONY: debug
debug: CXXFLAGS += -g
debug: $(TARGET)

.PHONY: release
release: CXXFLAGS += -O3
release: $(TARGET)

.PHONY: test
test: $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(OBJECTS) $(TEST_OBJECTS) $(CXXFLAGS) $(LIBS) -o $(TEST_TARGET) -pg

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) main.o
	$(CXX) $(OBJECTS) main.o $(CXXFLAGS) $(LIBS) -o $@ -pg

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -rf $(TARGET).dSYM
