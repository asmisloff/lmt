all: lmt.cpp RandomPairs.cpp
	g++ lmt.cpp RandomPairs.cpp Timer.cpp Reader.cpp -o lmt -O0 -Wall -Wextra