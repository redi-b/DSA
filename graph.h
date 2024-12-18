#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#include "queue.h"
#include "stack.h"

template <typename Type>
class Graph {
   private:
    std::unordered_map<Type, std::vector<Type>> adjList;

   public:
    Graph() {}

    void addEdge(Type from, Type to, bool isDirected = false) {
        adjList[from].push_back(to);
        if (!isDirected) {
            adjList[to].push_back(from);
        }
    }

    void printGraph() {
        for (const auto& pair : adjList) {
            std::cout << pair.first << ": ";
            for (const auto& neighbor : pair.second) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

    // Breadth-First Search
    void bfs(Type start) {
        if (adjList.find(start) == adjList.end()) {
            std::cout << "Start node not found in the graph.\n";
            return;
        }

        QueueLLB<Type> queue;
        std::set<Type> visited;

        queue.enqueue(start);
        visited.insert(start);

        while (!queue.isEmpty()) {
            Type current = queue.dequeue();

            std::cout << current << " ";

            for (const auto& neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    queue.enqueue(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        std::cout << "\n";
    }

    // Depth-First Search
    void dfs(Type start) {
        if (adjList.find(start) == adjList.end()) {
            std::cout << "Start node not found in the graph.\n";
            return;
        }

        StackLLB<Type> stack;
        std::set<Type> visited;

        stack.push(start);

        while (!stack.empty()) {
            Type current = stack.pop();

            if (visited.find(current) == visited.end()) {
                std::cout << current << " ";
                visited.insert(current);

                for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                    if (visited.find(*it) == visited.end()) {
                        stack.push(*it);
                    }
                }
            }
        }

        std::cout << "\n";
    }
};
