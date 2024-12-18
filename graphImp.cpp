#include <iostream>

#include "graph.h"

int main() {
    Graph<int> graph;

    // Adding edges (undirected graph)
    graph.addEdge(0, 0);
    // graph.addEdge(1, 3);
    // graph.addEdge(2, 4);
    // graph.addEdge(3, 5);
    // graph.addEdge(4, 6);
    // graph.addEdge(5, 6);

    // std::cout << "Graph representation:\n";
    // graph.printGraph();

    // std::cout << "\nBFS starting from node 1:\n";
    // graph.bfs(1);

    // std::cout << "\nDFS starting from node 1:\n";
    // graph.dfs(1);

    return 0;
}
