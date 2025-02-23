CC=g++
#x86_64-w64-mingw32-g++
CXXFLAGS= -std=c++11 #-static

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:*.cpp=.o)

project.exe:$(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@