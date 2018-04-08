CXXFLAGS = -std=c++11 -pedantic -Werror -Wall -g -I.
CXX = g++

run: main.o
	$(CXX) $(CXXFLAGS) -o run main.o Individual.o Population.o Gene.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp Individual.cpp Population.cpp Gene.cpp

clean:
	rm -f main.o Individual.o Population.o Gene.o run
	

