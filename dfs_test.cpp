#include "Graph.hpp"
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
Graph g;
g.addVertex(1);
g.addVertex(2);
g.addVertex(3);
g.addVertex(4);
g.addEdge(1, 2);
g.addEdge(1, 3);
g.addEdge(3, 4);

auto result = g.depthFirstSearch(false);

for (auto& u : result) {
    cout << "Vertices: " << u.first << " , attribute of DFS: " << get<0>(u.second) << " " << get<1>(u.second) << get<2>(u.second) << endl;
}
    return 0;
}

