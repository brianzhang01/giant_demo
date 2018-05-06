all: network giant

network: network.cpp
	g++ -o network.exe -O2 -std=c++11 network.cpp

giant: giant.cpp graph.cpp graph.hpp
	g++ -o giant.exe -O2 -std=c++11 giant.cpp graph.cpp

graph_test: graph_test.cpp graph.cpp graph.hpp catch.hpp
	g++ -o graph_test.exe -O2 -std=c++11 graph_test.cpp graph.cpp

clean:
	rm *.exe
