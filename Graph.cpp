#include "Graph.hpp"
#include <algorithm>
#include <limits>
using namespace std;

//===========================================
//Copy constructor
//Parameter: Graph other
//Construct a new graph with same adjacency list and sorted attribute
//===========================================
Graph::Graph(const Graph& other)
    : adjacencyList(other.adjacencyList), sorted(other.sorted) {}

//===========================================
//Assignment operator
//Parameter: Graph other
//Perform a deep copy of the graph
//===========================================
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        adjacencyList = other.adjacencyList;
        sorted = other.sorted;
    }
    return *this;
}

//===========================================
//addEdge
//Parameter: int u, int v
//Creates an edge that goes from u to v and add it to the adjacency list
//===========================================
void Graph::addEdge(int u, int v) {
    if (adjacencyList.find(u) == adjacencyList.end() || adjacencyList.find(v) == adjacencyList.end()) {
        throw VertexException("One or both vertices do not exist.");
    }
    adjacencyList[u].insert(v);
}

//===========================================
//remove Edge
//Parameter: int u, int v
//Remove an edge that goes from u to v and remove it to the adjacency list
//===========================================
void Graph::removeEdge(int u, int v) {
    if (adjacencyList.find(u) == adjacencyList.end() || adjacencyList[u].find(v) == adjacencyList[u].end()) {
        throw EdgeException("Edge does not exist.");
    }
    adjacencyList[u].erase(v);
}

//===========================================
//edgeIn
//Parameter: int u, int v
//Check for the existence an edge that goes from u to v
//===========================================
bool Graph::edgeIn(int u, int v) {
    return adjacencyList.find(u) != adjacencyList.end() && adjacencyList[u].find(v) != adjacencyList[u].end();
}

//===========================================
//deleteVertex
//Parameter: int u
//Removes all the edge associated to u
//===========================================
void Graph::deleteVertex(int u) {
    if (adjacencyList.find(u) == adjacencyList.end()) {
        throw VertexException("Vertex does not exist.");
    }
    adjacencyList.erase(u);
    for (auto& [key, neighbors] : adjacencyList) {
        neighbors.erase(u);
    }
    sorted.erase(remove(sorted.begin(), sorted.end(), u), sorted.end());
}

//===========================================
//addVertex
//Parameter: int u
//Create a new vertex u
//===========================================
void Graph::addVertex(int u) {
    if (adjacencyList.find(u) != adjacencyList.end()) {
        throw VertexException("Vertex already exists.");
    }
    adjacencyList[u] = unordered_set<int>();
    sorted.push_back(u);
}


//===========================================
//getOrdering
//Parameter: none
//return the topoligcal ordering of the graph
//===========================================
vector<int> Graph::getOrdering() {
    depthFirstSearch(true);
    return sorted;
}

//===========================================
//breadthFirstSearch
//Parameter: int s
//perform breadth first search at the vertex s
//===========================================
unordered_map<int, pair<int, int>> Graph::breadthFirstSearch(int s) {
    unordered_map<int, pair<int, int>> bfsMap;  // {vertex: {distance, parent}}
    queue<int> q;

    if (adjacencyList.find(s) ==adjacencyList.end()) {
        throw VertexException("Source vertex does not exist");
    }

    // Initialize distances and parents
    for (const auto& [vertex, _] : adjacencyList) {
        bfsMap[vertex] = {numeric_limits<int>::max(), -1};  // Infinite distance, no parent is -1
    }

    // BFS Initialization
    bfsMap[s] = {0, -1};  // Source vertex: distance 0, no parent
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adjacencyList[u]) {
            if (bfsMap[v].first == numeric_limits<int>::max()) {  // If not visited
                bfsMap[v] = {bfsMap[u].first + 1, u};  // Set distance and parent to u 
                q.push(v);
            }
        }
    }

    return bfsMap;
}

//===========================================
//depthFirstSearch
//Parameter: int s
//perform depth first search at the vertex s
//===========================================
unordered_map<int, tuple<int, int, int>> Graph::depthFirstSearch(bool sort) {
    unordered_map<int, tuple<int, int, int>> dfsMap;  // {vertex: {discovery, finish, parent}}
    unordered_map<int, string> color_list; // For coloring vertices
    int time = 0;
    sorted.clear();
    // Initialize all vertices to "white" (unvisited) and set parent to -1 (no parent)
    for (auto& u : adjacencyList) {
        color_list[u.first] = "white";
        dfsMap[u.first] = std::make_tuple(0, 0, -1);  
    }

    // DFS helper function DFS_VIST
    function<void(int)> DFS_VISIT = [&](int u) {
        time++;
        color_list[u] = "gray";  // Mark the vertex grey as being processed
        get<0>(dfsMap[u]) = time;  // Set the discovery time

        // Visit all neighbors
        for (auto& i : adjacencyList[u]) {
            if (color_list[i] == "white") {  // If the neighbor is unvisited
                get<2>(dfsMap[i]) = u;  // Set the parent of the neighbor
                DFS_VISIT(i);  // Recurse for the neighbor
            }
        }

        color_list[u] = "black";  // Mark the vertex as finished
        time++;  // Increment time for finish time
        get<1>(dfsMap[u]) = time;  // Set the finish time

        // If sort is true is requested, add the vertex to the sorted list
        if (sort) {
            sorted.push_back(u);  // Add the vertex to the sorted list after DFS is done
        }
    };

    // Perform DFS for all vertices
    for (auto& u : adjacencyList) {
        if (color_list[u.first] == "white") {
            DFS_VISIT(u.first);  // Start DFS from unvisited vertices
        }
    }
    // Reverse the sorted list to get topological order
    reverse(sorted.begin(), sorted.end());
    
    

    return dfsMap;  // Return the DFS map with discovery, finish times, and parent info
}




//===========================================
//readFromSTDIN
//Parameter: none
//function that populate a graph with the std in
//===========================================
Graph Graph::readFromSTDIN() {
    Graph g;

    int n, m;
    cin >> n >> m;  // Read number of vertices and edges

    for (int i = 1; i <= n; ++i) {
        g.addVertex(i);  // Add vertices
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);  // Add edges
    }

    return g;
}
