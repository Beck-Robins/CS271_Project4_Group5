#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "customexceptions.hpp"

class Graph {
private:
    std::unordered_map<int, std::unordered_set<int>> adjacencyList;
    std::vector<int> sorted;

public:
    // Constructors and Destructors
    Graph() = default;
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph() = default;

    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool edgeIn(int u, int v);
    void deleteVertex(int u);
    void addVertex(int u);

    void sortVertices();
    const std::vector<int>& getSortedVertices() const;
};

#endif // GRAPH_HPP

