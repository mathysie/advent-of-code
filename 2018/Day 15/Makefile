SOURCES=$(wildcard *.cpp)
TARGETS=$(SOURCES:.cpp=.o)
CXXFLAGS=-Wall -Wextra -g -Wconversion

all: $(TARGETS)
	g++ $(CXXFLAGS) -o solution $(TARGETS)

clean:
	rm -f core *.o