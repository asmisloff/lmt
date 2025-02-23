all: lmt.cpp RandomPairs.cpp
	g++ lmt.cpp RandomPairs.cpp Timer.cpp -o lmt -O0 -Wall -Wextra