CXXFLAGS = -std=c++11 -pedantic -Werror -Wall -I.
CXX = g++

run: main.o
	$(CXX) $(CXXFLAGS) -o run main.o Individual.o Population.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp Individual.cpp Population.cpp

clean:
	rm -f main.o Individual.o Population.o run
	

