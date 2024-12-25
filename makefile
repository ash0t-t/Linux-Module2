all: find-max

find-max: main.cpp
	g++ -std=c++17 -pthread -o find-max main.cpp

clean:
	rm -f find-max
