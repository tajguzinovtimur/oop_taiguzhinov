CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TARGET = variant20_test

all: $(TARGET)

$(TARGET): src/FixedBlockMemoryResource.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run