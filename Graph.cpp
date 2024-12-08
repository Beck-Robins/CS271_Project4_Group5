#include "Graph.hpp"
#include <algorithm>
#include <stdexcept>

// Copy constructor
Graph::Graph(const Graph& other)
    : adjacencyList(other.adjacencyList), sorted(other.sorted) {}

// Copy assignment operator
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        adjacencyList = other.adjacencyList;
        sorted = other.sorted;
    }
    return *this;
}

// Add an edge from u to v
void Graph::addEdge(int u, int v) {
    if (adjacencyList.find(u) == adjacencyList.end() || adjacencyList.find(v) == adjacencyList.end()) {
        throw VertexException("One or both vertices do not exist.");
    }
    adjacencyList[u].insert(v);
}

// Remove edge (u, v)
void Graph::removeEdge(int u, int v) {
    if (adjacencyList.find(u) == adjacencyList.end() || adjacencyList[u].find(v) == adjacencyList[u].end()) {
        throw EdgeException("Edge does not exist.");
    }
    adjacencyList[u].erase(v);
}

// Check if edge (u, v) exists
bool Graph::edgeIn(int u, int v) {
    return adjacencyList.find(u) != adjacencyList.end() && adjacencyList[u].find(v) != adjacencyList[u].end();
}

// Delete a vertex u and all its edges
void Graph::deleteVertex(int u) {
    if (adjacencyList.find(u) == adjacencyList.end()) {
        throw VertexException("Vertex does not exist.");
    }
    adjacencyList.erase(u);
    for (auto& [key, neighbors] : adjacencyList) {
        neighbors.erase(u);
    }
    sorted.erase(std::remove(sorted.begin(), sorted.end(), u), sorted.end());
}

// Add a new vertex u
void Graph::addVertex(int u) {
    if (adjacencyList.find(u) != adjacencyList.end()) {
        throw VertexException("Vertex already exists.");
    }
    adjacencyList[u] = std::unordered_set<int>();
    sorted.push_back(u);
}

// Sort vertices
void Graph::sortVertices() {
    std::sort(sorted.begin(), sorted.end());
}

// Get sorted vertices
const std::vector<int>& Graph::getSortedVertices() const {
    return sorted;
}

