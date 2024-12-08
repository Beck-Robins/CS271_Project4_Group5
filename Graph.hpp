#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <queue>
#include "customexceptions.hpp"

class Graph {
private:
    std::unordered_map<int, std::unordered_set<int>> adjacencyList;
    std::vector<int> sorted;  // Stores topologically sorted vertices

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
    std::unordered_map<int, std::pair<int, int>> breadthFirstSearch(int s);
    std::unordered_map<int, std::tuple<int, int, int>> depthFirstSearch(bool sort = false);

    // Utility Methods
    void sortVertices();
    const std::vector<int>& getSortedVertices() const;
    std::vector<int> getOrdering() const;

    // Input/Output
    static Graph readFromSTDIN();
};

#endif
