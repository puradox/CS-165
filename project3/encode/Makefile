ifdef SYSTEMROOT
	TARGET = LZ.exe
	TEST_TARGET = test.exe
else
	TARGET = LZ
	TEST_TARGET = test
endif

LIBS =
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

HEADERS = stree.hpp config.hpp writer.hpp
OBJECTS = stree.o   config.o   writer.o

TEST_HEADERS = catch.hpp
TEST_OBJECTS = catch.o   stree_tests.o   writer_tests.o

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
	-rm -f $(TEST_TARGET)
	-rm -rf $(TEST_TARGET).dSYM
