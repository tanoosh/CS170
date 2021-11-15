main: main.o node.o puzzle.o
	g++ main.o node.o puzzle.o -o main

main.o: main.cpp
	g++ -c main.cpp

node.o: Node.cpp node.h
	g++ -c Node.cpp

puzzle.o: puzzle.cpp puzzle.h
	g++ -c puzzle.cpp

clean: 
	rm *.o output
