#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <queue>
#include "customexceptions.hpp"
using namespace std;

class Graph {
private:
    map<int, unordered_set<int>> adjacencyList;
    vector<int> sorted; 

public:
    
    // Constructors and Destructors
    Graph() = default;
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph() = default;

    // Methods
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool edgeIn(int u, int v);
    void deleteVertex(int u);
    void addVertex(int u);

    // Search Algorithms
    unordered_map<int, pair<int, int>> breadthFirstSearch(int s);
    unordered_map<int, tuple<int, int, int>> depthFirstSearch(bool sort);

    // Utility Methods
    vector<int> getOrdering();

    // Input/Output
    static Graph readFromSTDIN(); 
};

#endif
