all: network giant

network: network.cpp
	g++ -o network.exe -O2 -std=c++11 network.cpp

giant: giant.cpp graph.cpp graph.hpp
	g++ -o giant.exe -O2 -std=c++11 giant.cpp graph.cpp

test_main.o: test_main.cpp catch.hpp
	g++ -c test_main.cpp -std=c++11

graph_test: graph_test.cpp graph.cpp graph.hpp catch.hpp test_main.o
	g++ -o graph_test.exe -std=c++11 graph_test.cpp graph.cpp test_main.o
	./graph_test.exe

clean:
	rm -f *.exe *.o
