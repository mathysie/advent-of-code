SOURCES=$(wildcard *.cpp)
TARGETS=$(SOURCES:.cpp=.o)
CXXFLAGS=-Wall -Wextra -g -Wconversion

all: $(TARGETS)
	g++ $(CXXFLAGS) -o solutions_1 $(TARGETS)

clean:
	rm -f core *.o solutions_1
