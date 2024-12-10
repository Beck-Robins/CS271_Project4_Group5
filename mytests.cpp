//==========================================
//Damian Nguyen, Beck Robins
//Project 4
//mytests.cpp
//Contains the tests for class Graph
//==========================================


#include "Graph.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int passedTests = 0;  // Counter for passed tests
int failedTests = 0;  // Counter for failed tests

// Helper function to record test results
void recordTestResult(bool passed) {
    if (passed) {
        ++passedTests;
    } else {
        ++failedTests;
    }
}

// Test 1: Adding vertices
void testAddVertex() {
    cout << "Test: Add Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        cout << "-> Passed: Vertices added successfully.\n";
        recordTestResult(true);
    } catch (...) {
        cout << "-> Failed: Exception thrown during addVertex.\n";
        recordTestResult(false);
    }
}

// Test 2: Adding an edge
void testAddEdge() {
    cout << "Test: Add Edge\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        if (g.edgeIn(1, 2)) {
            cout << "-> Passed: Edge 1->2 added successfully.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Edge not found after adding.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during addEdge.\n";
        recordTestResult(false);
    }
}

// Test 3: Checking edge existence
void testEdgeIn() {
    cout << "Test: Edge Existence\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        if (g.edgeIn(1, 2) && !g.edgeIn(2, 1)) {
            cout << "-> Passed: Edge existence verified correctly.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Incorrect edge existence detection.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during edgeIn.\n";
        recordTestResult(false);
    }
}

// Test 4: Removing an edge
void testRemoveEdge() {
    cout << "Test: Remove Edge\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        g.removeEdge(1, 2);
        if (!g.edgeIn(1, 2)) {
            cout << "-> Passed: Edge 1->2 removed successfully.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Edge still exists after removal.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during removeEdge.\n";
        recordTestResult(false);
    }
}

// Test 5: Deleting a vertex
void testDeleteVertex() {
    cout << "Test: Delete Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.deleteVertex(1);
        if (!g.edgeIn(1, 2) && !g.edgeIn(2, 1)) {
            cout << "-> Passed: Vertex 1 deleted successfully.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Vertex or edges still exist after deletion.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during deleteVertex.\n";
        recordTestResult(false);
    }
}

// Test 6: Adding duplicate vertex
void testAddDuplicateVertex() {
    cout << "Test: Add Duplicate Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(1);  // Should throw exception
        cout << "-> Failed: Exception not thrown for duplicate vertex.\n";
        recordTestResult(false);
    } catch (const VertexException&) {
        cout << "-> Passed: Exception thrown for duplicate vertex.\n";
        recordTestResult(true);
    } catch (...) {
        cout << "-> Failed: Incorrect exception type thrown.\n";
        recordTestResult(false);
    }
}

// Test 7: Breadth-First Search
void testBreadthFirstSearch() {
    cout << "Test: Breadth-First Search (BFS)\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        g.addVertex(4);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);

        auto bfsResult = g.breadthFirstSearch(1);
        if (bfsResult[1].first == 0 && bfsResult[2].first == 1 && bfsResult[3].first == 1 && bfsResult[4].first == 2) {
            cout << "-> Passed: BFS distances and parents are correct.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Incorrect BFS results.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during BFS.\n";
        recordTestResult(false);
    }
}

// Test 8: Depth-First Search
void testDepthFirstSearch() {
    cout << "Test: Depth-First Search (DFS)\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        g.addVertex(4);
        g.addVertex(5);
        g.addVertex(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(3, 4);
        g.addEdge(4, 6);
        g.addEdge(6, 5);

        auto dfsResult = g.depthFirstSearch(true);
        for (auto& u : dfsResult) {
            cout << "Vertex: " << u.first
                 << ", Discovery Time: " << get<0>(u.second)
                 << ", Finish Time: " << get<1>(u.second)
                 << ", Parent: " << get<2>(u.second) << endl;
        }

        if (get<0>(dfsResult[1]) == 1 && get<1>(dfsResult[1]) > 0 &&  // Discovery and finish times are valid
            get<2>(dfsResult[2]) == 1 &&                              // Parent of 2 is 1
            get<2>(dfsResult[4]) == 3) {                              // Parent of 4 is 3
            cout << "-> Passed: DFS discovery/finish times and parents are correct.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Incorrect DFS results.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during DFS.\n";
        recordTestResult(false);
    }
}

// Test 9: Testing getOrdering
void testGetOrdering() {
    cout << "Test: Get Ordering\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.depthFirstSearch(true);  // Generate topological ordering
        auto ordering = g.getOrdering();
        if (!ordering.empty() && ordering.size() == 3) {
            cout << "-> Passed: Ordering retrieved successfully.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Ordering incorrect.");
        }
    } catch (...) {
        cout << "-> Failed: Exception thrown during getOrdering.\n";
        recordTestResult(false);
    }
}

// Test 10: Testing readFromSTDIN
void testReadFromSTDIN() {
    cout << "Test: Read From STDIN\n";
    try {
        // Simulating STDIN input using a string stream
        istringstream input("4 3\n1 2\n2 3\n3 4\n");
        cin.rdbuf(input.rdbuf());  // Redirect cin to the string stream

        Graph g = Graph::readFromSTDIN();
        if (g.edgeIn(1, 2) && g.edgeIn(2, 3) && g.edgeIn(3, 4)) {
            cout << "-> Passed: Graph read from STDIN correctly.\n";
            recordTestResult(true);
        } else {
            throw runtime_error("Graph structure incorrect.");
        }

        cin.rdbuf(nullptr);  // Restore original cin buffer
    } catch (...) {
        cout << "-> Failed: Exception thrown during readFromSTDIN.\n";
        recordTestResult(false);
    }
}

// Main driver to run all tests
int main() {
    testAddVertex();
    testAddEdge();
    testEdgeIn();
    testRemoveEdge();
    testDeleteVertex();
    testAddDuplicateVertex();
    testBreadthFirstSearch();
    testDepthFirstSearch();
    testGetOrdering();
    testReadFromSTDIN();

    cout << "\nSummary:\n";
    cout << "Tests Passed: " << passedTests << "\n";
    cout << "Tests Failed: " << failedTests << "\n";

    return 0;
}
