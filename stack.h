#include <iostream>

#include "arrayList.h"
#include "linkedList.h"

template <typename Type>
class StackAB {
   private:
    int size;
    int top;
    Type* stack;

   public:
    StackAB(int size = 1) {
        this->size = size;
        this->stack = new Type[size];
        this->top = -1;
    }

    void push(Type value) {
        if (this->size == top + 1) {
            std::cout << "Stack is full!" << std::endl;
            return;
        }

        stack[++top] = value;
    }
    Type pop() {
        if (size == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return Type();
        }

        Type value = stack[top--];
        return value;
    }
    Type peek() {
        if (top >= 0) {
            return stack[top];
        }
        return Type();
    }
    void display() {
        std::cout << "TOP\n";
        for (int i = top; i >= 0; i--) {
            std::cout << "| " << stack[i] << " |\n";
        }
        std::cout << "BOTTOM\n";
    }
    bool isEmpty() {
        return top == -1;
    }
};

template <typename Type>
class StackALB {
   private:
    arrayList<Type> list;

   public:
    StackALB() {}
    StackALB(int size) {
    }
    void push(Type value) {
        list.insertValue(value);
    }
    Type pop() {
        if (list.getSize() == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return Type();
        }

        int index = list.getSize() - 1;
        Type value = list.getValue(index);
        list.deleteValue(index);

        return value;
    }
    Type peek() {
        if (list.getSize() > 0) {
            Type value = list.getValue(list.getSize() - 1);
            return value;
        }
        return Type();
    }
    void display() {
        std::cout << "TOP\n";
        for (int i = list.getSize() - 1; i >= 0; i--) {
            std::cout << "| " << list.getValue(i) << " |\n";
        }
        std::cout << "BOTTOM\n";
    }
    int getSize() {
        return list.getSize();
    }
    bool isEmpty() {
        return list.getSize() == 0;
    }
};

template <typename Type>
class StackLLB {
   private:
    DoublyLinkedList<Type>* list;

   public:
    StackLLB() {
        list = new DoublyLinkedList<Type>();
    }
    void push(Type value) {
        list->insertValue(value);
    }
    Type pop() {
        if (list->getSize() == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return Type();
        }

        Type value = list->getTail()->data;
        list->deleteByPosition(list->getSize());

        return value;
    }
    Type peek() {
        if (list->getSize() > 0) {
            Type value = list->getTail()->data;
            return value;
        }
        return Type();
    }
    void display() {
        DNode<Type>* end = list->getTail();
        while (end != nullptr) {
            std::cout << "| " << end->data << " |\n";
            end = end->prev;
        }
        std::cout << "-----\n";
    }
    int getSize() {
        return list->getSize();
    }
    bool isEmpty() {
        return list->getSize() == 0;
    }
};
