#include "Graph.hpp"
#include <iostream>

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
    std::cout << "Test: Add Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        std::cout << "-> Passed: Vertices added successfully.\n";
        recordTestResult(true);
    } catch (...) {
        std::cout << "-> Failed: Exception thrown during addVertex.\n";
        recordTestResult(false);
    }
}

// Test 2: Adding an edge
void testAddEdge() {
    std::cout << "Test: Add Edge\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        if (g.edgeIn(1, 2)) {
            std::cout << "-> Passed: Edge 1->2 added successfully.\n";
            recordTestResult(true);
        } else {
            throw std::runtime_error("Edge not found after adding.");
        }
    } catch (...) {
        std::cout << "-> Failed: Exception thrown during addEdge.\n";
        recordTestResult(false);
    }
}

// Test 3: Checking edge existence
void testEdgeIn() {
    std::cout << "Test: Edge Existence\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        if (g.edgeIn(1, 2) && !g.edgeIn(2, 1)) {
            std::cout << "-> Passed: Edge existence verified correctly.\n";
            recordTestResult(true);
        } else {
            throw std::runtime_error("Incorrect edge existence detection.");
        }
    } catch (...) {
        std::cout << "-> Failed: Exception thrown during edgeIn.\n";
        recordTestResult(false);
    }
}

// Test 4: Removing an edge
void testRemoveEdge() {
    std::cout << "Test: Remove Edge\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.addEdge(1, 2);
        g.removeEdge(1, 2);
        if (!g.edgeIn(1, 2)) {
            std::cout << "-> Passed: Edge 1->2 removed successfully.\n";
            recordTestResult(true);
        } else {
            throw std::runtime_error("Edge still exists after removal.");
        }
    } catch (...) {
        std::cout << "-> Failed: Exception thrown during removeEdge.\n";
        recordTestResult(false);
    }
}

// Test 5: Deleting a vertex
void testDeleteVertex() {
    std::cout << "Test: Delete Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(2);
        g.deleteVertex(1);
        if (!g.edgeIn(1, 2) && !g.edgeIn(2, 1)) {
            std::cout << "-> Passed: Vertex 1 deleted successfully.\n";
            recordTestResult(true);
        } else {
            throw std::runtime_error("Vertex or edges still exist after deletion.");
        }
    } catch (...) {
        std::cout << "-> Failed: Exception thrown during deleteVertex.\n";
        recordTestResult(false);
    }
}

// Test 6: Adding duplicate vertex
void testAddDuplicateVertex() {
    std::cout << "Test: Add Duplicate Vertex\n";
    try {
        Graph g;
        g.addVertex(1);
        g.addVertex(1);  // Should throw exception
        std::cout << "-> Failed: Exception not thrown for duplicate vertex.\n";
        recordTestResult(false);
    } catch (const VertexException&) {
        std::cout << "-> Passed: Exception thrown for duplicate vertex.\n";
        recordTestResult(true);
    } catch (...) {
        std::cout << "-> Failed: Incorrect exception type thrown.\n";
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

    std::cout << "\nSummary:\n";
    std::cout << "Tests Passed: " << passedTests << "\n";
    std::cout << "Tests Failed: " << failedTests << "\n";

    return 0;
}
