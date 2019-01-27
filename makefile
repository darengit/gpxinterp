a.out: tinyxml2.o
	g++ -Wall -std=c++14 -g main.cpp tinyxml2.o

tinyxml2.o:
	g++ -Wall -std=c++14 -g -c tinyxml2.cpp -o tinyxml2.o

clean:
	rm a.out
	rm tinyxml2.o
