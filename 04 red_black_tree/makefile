# CXX = g++
# FLAGS = -std=c++11

# SRCS = $(wildcard *.cpp)
# OBJS = $(SRCS:*.cpp=.o)


# RBTree : $(OBJS)
# 	$(CXX) $(FLAGS) -o $@ $^

# $(OBJS) : $(SRCS)
# 	$(CXX) $(FLAGS) -o $@ $<

CXX = g++
FLAGS = -std=c++11

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

RBTree: $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) RBTree