parser: main.o parser.o 
	g++ main.o parser.o -o bin/parser

main.o: main.cpp
	g++ --std=c++11 main.cpp -o main.o

parser.o: parser.cpp parser.hpp
	g++ --std=c++11 parser.cpp -o parser.o

clean:
	rm *.o bin/parser