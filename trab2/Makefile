CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS =

SRC = riscv_reader.cpp $(wildcard instructions/*.cpp) memory.cpp decoder.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = riscv_simulator

all: $(TARGET)

$(TARGET): $(OBJ)	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
