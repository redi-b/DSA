#include <iostream>

#include "queue.h"
#include "stack.h"

template <typename Type>
class BSTNode {
   public:
    Type data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Type value) : data(value), left(nullptr), right(nullptr) {}
};

template <class Type>
class BSTree {
   private:
    BSTNode<Type>* root;

    // LPR
    void inOrderTraversal(BSTNode<Type>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    // PLR
    void preOrderTraversal(BSTNode<Type>* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    // LRP
    void postOrderTraversal(BSTNode<Type>* node) {
        if (node != nullptr) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            std::cout << node->data << " ";
        }
    }

    void deleteTree(BSTNode<Type>* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void clearTree() {
        deleteTree(root);
    }

   public:
    BSTree() : root(nullptr) {};
    ~BSTree() {
        clearTree();
    };

    void insert(Type value) {
        BSTNode<Type>* newNode = new BSTNode<Type>(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        BSTNode<Type>* current = root;
        BSTNode<Type>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (current->data > value) {
                current = parent->left;
            } else {
                current = parent->right;
            }
        }

        if (parent->data > value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    bool search(BSTNode<Type>* node, Type value) {
        if (node == nullptr)
            return false;
        else if (node->data == value)
            return true;
        else if (node->data > value)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    bool search(Type value) {
        return search(root, value);
    }

    void traverseInOrder() {
        inOrderTraversal(root);
        std::cout << "\n";
    }

    void traversePreOrder() {
        preOrderTraversal(root);
        std::cout << "\n";
    }

    void traversePostOrder() {
        postOrderTraversal(root);
        std::cout << "\n";
    }

    void dft() {
        if (root == nullptr) {
            std::cout << "Tree is empty!\n";
            return;
        }

        StackLLB<BSTNode<Type>*> stack;

        stack.push(root);

        while (!stack.isEmpty()) {
            BSTNode<Type>* current = stack.pop();
            std::cout << current->data << " ";

            if (current->right != nullptr)
                stack.push(current->right);
            if (current->left != nullptr)
                stack.push(current->left);
        }

        std::cout << "\n";
    }

    void bft() {
        if (root == nullptr) {
            std::cout << "Tree is empty!\n";
            return;
        }

        QueueLLB<BSTNode<Type>*> queue;
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            BSTNode<Type>* current = queue.dequeue();
            std::cout << current->data << " ";

            if (current->left != nullptr)
                queue.enqueue(current->left);
            if (current->right != nullptr)
                queue.enqueue(current->right);
        }
        std::cout << "\n";
    }

    void deleteByMerging(Type value) {
        BSTNode<Type>* node = root;
        BSTNode<Type>* parent = nullptr;

        while (node != nullptr && node->data != value) {
            parent = node;
            if (value < node->data)
                node = node->left;
            else
                node = node->right;
        }

        if (node == nullptr) {
            std::cout << "Value not found!\n";
            return;
        }

        BSTNode<Type>* nodeToDelete = node;

        if (node->left == nullptr)
            node = node->right;
        else if (node->right == nullptr)
            node = node->left;
        else {
            BSTNode<Type>* leftSubtree = node->left;
            BSTNode<Type>* rightSubtree = node->right;

            BSTNode<Type>* rightmost = leftSubtree;
            while (rightmost->right != nullptr)
                rightmost = rightmost->right;

            rightmost->right = rightSubtree;
            node = leftSubtree;
        }

        if (parent == nullptr)
            root = node;
        else if (parent->left == nodeToDelete)
            parent->left = node;
        else
            parent->right = node;

        delete nodeToDelete;
    }

    void deleteByCopying(Type value) {
        BSTNode<Type>* node = root;
        BSTNode<Type>* parent = nullptr;

        while (node != nullptr && node->data != value) {
            parent = node;
            if (value < node->data)
                node = node->left;
            else
                node = node->right;
        }

        if (node == nullptr) {
            std::cout << "Value not found!\n";
            return;
        }

        BSTNode<Type>* nodeToDelete = node;

        if (node->left == nullptr || node->right == nullptr) {
            node = (node->left != nullptr) ? node->left : node->right;
        } else {
            BSTNode<Type>* successorParent = node;
            BSTNode<Type>* successor = node->right;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            node->data = successor->data;
            if (successorParent->left == successor)
                successorParent->left = successor->right;
            else
                successorParent->right = successor->right;

            nodeToDelete = successor;
        }

        if (parent == nullptr)
            root = node;
        else if (parent->left == nodeToDelete)
            parent->left = node;
        else
            parent->right = node;

        delete nodeToDelete;
    }

    void clear() {
        clearTree();
        root = nullptr;
    }
};
