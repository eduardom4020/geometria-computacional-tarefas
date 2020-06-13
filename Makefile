all: homework1 homework2
	clear

homework2: homework2.o
	g++ -std=c++1y -o ./build/homework2 ./build/compiled/homework2.o

homework2.o:
	g++ -std=c++1y -o ./build/compiled/homework2.o -c ./homework2.cpp

homework1: homework1.o
	g++ -std=c++1y -o ./build/homework1 ./build/compiled/homework1.o

homework1.o:
	g++ -std=c++1y -o ./build/compiled/homework1.o -c ./homework1.cpp

clean:
	rm -rf **/*.o **/**/*.o **/*.bin **/*.exe