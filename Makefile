CXXFLAGS = -g -Wall --std=c++11

all: main.o profile.o network.o

	g++ $(CXXFLAGS) -o main main.o profile.o network.o

main: main.o profile.o network.o

	g++ $(CXXFLAGS) -o main main.o profile.o network.o


tests: tests.o profile.o network.o

	g++ $(CXXFLAGS) -o tests tests.o profile.o network.o





profile.o: profile.cpp profile.h
network.o: network.cpp network.h
main.o: main.cpp

tests.o: tests.cpp doctest.h

clean:
	rm -f *.o
