parser: parser.o main.o
	g++ parser.o main.o -o bin/parser

parser.o: parser.cpp parser.hpp
	g++ --std=c++11 parser.cpp -o parser.o

main.o: main.cpp
	g++ --std=c++11 main.cpp -o main.o

clean:
	rm *.o bin/parser