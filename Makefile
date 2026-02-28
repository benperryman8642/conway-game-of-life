CXX = clang++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic
TARGET = build/life

SRC = src/main.cpp src/grid.cpp src/life.cpp src/simulation.cpp

all:
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build