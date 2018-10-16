parser: main.o parser.o instructionList.o
	g++ main.o parser.o instructionList.o -o bin/parser

main.o: main.cpp
	g++ --std=c++11 -c main.cpp

parser.o: parser.cpp parser.hpp
	g++ --std=c++11 -c parser.cpp

instructionList.o: instructionList.cpp instructionList.hpp
	g++ --std=c++11 -c instructionList.cpp

clean:
	rm *.o bin/parser