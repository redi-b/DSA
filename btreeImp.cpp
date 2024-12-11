#include <iostream>

#include "btree.h"

int main() {
    BSTree<int> bsTree;

    bsTree.insert(5);
    bsTree.insert(7);
    bsTree.insert(10);
    bsTree.insert(6);
    bsTree.insert(4);
    bsTree.insert(8);
    bsTree.insert(9);

    std::cout << "In Order Traversal: ";
    bsTree.traverseInOrder();
    std::cout << "Pre Order Traversal: ";
    bsTree.traversePreOrder();
    std::cout << "Post Order Traversal: ";
    bsTree.traversePostOrder();
    std::cout << "Depth First Traversal: ";
    bsTree.dft();
    std::cout << "Breadth First Traversal: ";
    bsTree.bft();
    std::cout << "Search for 9: " << ((bsTree.search(9)) ? "Found!\n" : "Not Found!\n");
    std::cout << "Search for 8: " << ((bsTree.search(8)) ? "Found!\n" : "Not Found!\n");
    std::cout << "Search for 4: " << ((bsTree.search(4)) ? "Found!\n" : "Not Found!\n");
    return 0;
}

