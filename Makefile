all: lmt.cpp RandomSequence.cpp
	g++ lmt.cpp RandomSequence.cpp -o lmt -O0 -Wall -Wextra