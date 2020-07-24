all: homework1 homework2 homework3 homework4
	clear

homework4: homework4.o
	g++ -std=c++1y -o ./build/homework4 ./build/compiled/homework4.o

homework4.o:
	g++ -std=c++1y -o ./build/compiled/homework4.o -c ./homework4.cpp

homework3: homework3.o
	g++ -std=c++1y -o ./build/homework3 ./build/compiled/homework3.o

homework3.o:
	g++ -std=c++1y -o ./build/compiled/homework3.o -c ./homework3.cpp

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