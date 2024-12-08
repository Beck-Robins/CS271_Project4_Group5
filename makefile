mytests: mytests.cpp graph.o
	g++ -std=c++17 -g -o mytests mytests.cpp graph.o
	./mytests

graph.o: Graph.cpp Graph.hpp
	g++ -std=c++17 -g -c Graph.cpp -o graph.o

clean:
	rm -f mytests graph.o
