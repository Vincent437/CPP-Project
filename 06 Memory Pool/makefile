CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
TARGET = mem_pool
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
.PHONY: clean
clean:
	rm -f *.o $(TARGET)