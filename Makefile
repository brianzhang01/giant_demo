all: giant

giant: giant.cpp graph.cpp graph.hpp
	g++ -o giant.exe -O2 -std=c++11 giant.cpp graph.cpp

clean:
	rm -f *.exe *.o
