#include <iostream>
#include <set>

#include "arrayList.h"
#include "linkedList.h"
#include "queue.h"
#include "stack.h"

template <typename Type>
class Graph {
   private:
    arrayList<SinglyLinkedList<Type>*> adjList;
    int nodes;

   public:
    Graph() : nodes(0) {
        for (int i = 0; i < adjList.getSize(); i++) {
            adjList.insertValue(new SinglyLinkedList<Type>());
        }
    }

    ~Graph() {
        for (int i = 0; i < nodes; ++i) {
            delete adjList.getValue(i);
        }
    }

    void addEdge(int from, int to, bool isDirected = false) {
        adjList.getValue(from)->insertValue(to);

        // if (!isDirected) {
        // adjList.getValue(to)->insertValue(from);
        // }
        std::cout << "add\n";
    }

    void printGraph() {
        for (int i = 0; i < nodes; ++i) {
            std::cout << i << ": ";
            SinglyLinkedList<Type>* neighbors = adjList.getValue(i);

            if (neighbors->getSize() == 0) {
                std::cout << "Empty";
            } else {
                neighbors->traverse([](Type data) { std::cout << data << " "; });
            }
            std::cout << "\n";
        }
    }

    // Breadth-First Search
    void bfs(int start) {
        if (start >= nodes) {
            std::cout << "Start node out of bounds.\n";
            return;
        }

        QueueLLB<int> queue;
        std::set<int> visited;

        queue.enqueue(start);
        visited.insert(start);

        while (!queue.isEmpty()) {
            int current = queue.dequeue();
            std::cout << current << " ";

            SinglyLinkedList<Type>* neighbors = adjList.getValue(current);
            neighbors->traverse([&](Type neighbor) {
                if (visited.find(neighbor) == visited.end()) {
                    queue.enqueue(neighbor);
                    visited.insert(neighbor);
                }
            });
        }
        std::cout << "\n";
    }

    // Depth-First Search
    void dfs(int start) {
        if (start >= nodes) {
            std::cout << "Start node out of bounds.\n";
            return;
        }

        StackLLB<int> stack;
        std::set<int> visited;

        stack.push(start);

        while (!stack.isEmpty()) {
            int current = stack.pop();

            if (visited.find(current) == visited.end()) {
                std::cout << current << " ";
                visited.insert(current);

                SinglyLinkedList<Type>* neighbors = adjList.getValue(current);
                neighbors->traverse([&](Type neighbor) {
                    if (visited.find(neighbor) == visited.end()) {
                        stack.push(neighbor);
                    }
                });
            }
        }
        std::cout << "\n";
    }
};
