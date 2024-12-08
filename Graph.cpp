#include "Graph.hpp"
#include <algorithm>
#include <limits>

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

// Remove the edge (u, v)
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

// Return a copy of the topologically sorted vertices
std::vector<int> Graph::getOrdering() const {
    return sorted;
}

// Perform Breadth-First Search (BFS)
std::unordered_map<int, std::pair<int, int>> Graph::breadthFirstSearch(int s) {
    std::unordered_map<int, std::pair<int, int>> bfsMap;  // {vertex: {distance, parent}}
    std::queue<int> q;

    // Initialize distances and parents
    for (const auto& [vertex, _] : adjacencyList) {
        bfsMap[vertex] = {std::numeric_limits<int>::max(), -1};  // Infinite distance, no parent
    }

    // BFS Initialization
    bfsMap[s] = {0, -1};  // Source vertex: distance 0, no parent
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adjacencyList[u]) {
            if (bfsMap[v].first == std::numeric_limits<int>::max()) {  // If not visited
                bfsMap[v] = {bfsMap[u].first + 1, u};  // Set distance and parent
                q.push(v);
            }
        }
    }

    return bfsMap;
}

// Perform Depth-First Search (DFS)
std::unordered_map<int, std::tuple<int, int, int>> Graph::depthFirstSearch(bool sort) {
    std::unordered_map<int, std::tuple<int, int, int>> dfsMap;  // {vertex: {discovery, finish, parent}}
    std::unordered_map<int, bool> visited;
    std::vector<int> topoOrder;
    int time = 0;

    // Helper function for DFS visit
    std::function<void(int)> dfsVisit = [&](int u) {
        visited[u] = true;
        time++;
        std::get<0>(dfsMap[u]) = time;  // Discovery time

        for (int v : adjacencyList[u]) {
            if (!visited[v]) {
                std::get<2>(dfsMap[v]) = u;  // Set parent
                dfsVisit(v);
            }
        }

        time++;
        std::get<1>(dfsMap[u]) = time;  // Finish time
        topoOrder.push_back(u);  // Add to topoOrder as finished
    };

    // Initialize the DFS map
    for (const auto& [vertex, _] : adjacencyList) {
        dfsMap[vertex] = {0, 0, -1};  // discovery, finish, parent
        visited[vertex] = false;
    }

    // Perform DFS
    for (const auto& [vertex, _] : adjacencyList) {
        if (!visited[vertex]) {
            dfsVisit(vertex);
        }
    }

    // If sorting is required, reverse the topoOrder and store in sorted
    if (sort) {
        std::reverse(topoOrder.begin(), topoOrder.end());
        sorted = topoOrder;
    }

    return dfsMap;
}

// Static method to read graph from STDIN
Graph Graph::readFromSTDIN() {
    Graph g;

    int n, m;
    std::cin >> n >> m;  // Read number of vertices and edges

    for (int i = 1; i <= n; ++i) {
        g.addVertex(i);  // Add vertices
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);  // Add edges
    }

    return g;
}
