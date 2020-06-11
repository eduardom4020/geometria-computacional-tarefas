# My first makefile

COMPILED_PATHS = ./build/compiled/homework1.o

REQUISITES = 

all: homework1
	clear

homework1: $(REQUISITES) main.o
	g++ -std=c++1y -o ./build/homework1 $(COMPILED_PATHS)

main.o: $(REQUISITES)
	g++ -std=c++1y -o ./build/compiled/homework1.o -c ./homework1.cpp

clean:
	rm -rf **/*.o **/**/*.o **/*.bin **/*.exe