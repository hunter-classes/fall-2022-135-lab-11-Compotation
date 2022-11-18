CXXFLAGS = -g -Wall --std=c++11

all: main.o profile.o

	g++ $(CXXFLAGS) -o main main.o profile.o

main: main.o profile.o

	g++ $(CXXFLAGS) -o main main.o profile.o


tests: tests.o profile.o

	g++ $(CXXFLAGS) -o tests tests.o profile.o





profile.o: profile.cpp profile.h
main.o: main.cpp

tests.o: tests.cpp doctest.h

clean:
	rm -f *.o
