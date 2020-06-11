# My first makefile

COMPILED_PATHS = ./build/compiled/main.o

REQUISITES = 

all: homework1
	clear

homework1: $(REQUISITES) main.o
	g++ -std=c++1y -o ./build/homework1 $(COMPILED_PATHS)

main.o: $(REQUISITES)
	g++ -std=c++1y -o ./build/compiled/main.o -c ./main.cpp

clean:
	rm -rf *.o *~ homework1