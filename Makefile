parser: main.o parser.o 
	g++ main.o parser.o -o bin/parser

main.o: main.cpp
	g++ --std=c++11 -c main.cpp

parser.o: parser.cpp parser.hpp
	g++ --std=c++11 -c parser.cpp

clean:
	rm *.o bin/parser