# Makefile for rational number calculator
# CSE 374, 13wi  HP

calc: rational.o scan.o parse.o calc.o
	g++ -Wall -g -o calc calc.o rational.o scan.o parse.o

rational.o: rational.cpp rational.h
	g++ -Wall -g -c rational.cpp

scan.o: scan.cpp token.h scan.h
	g++ -Wall -g -c scan.cpp

parse.o: parse.cpp rational.h token.h scan.h
	g++ -Wall -g -c parse.cpp

calc.o: calc.cpp rational.h token.h scan.h parse.h
	g++ -Wall -g -c calc.cpp

clean:
	rm -f *.o *~ calc
