#include <iostream>

#include "linkedList.h"

template <class Type>
class QueueAB {
   protected:
    int size, capacity;
    int front, rear;
    Type* queue;

   public:
    QueueAB(int size) : capacity(size) {
        queue = new Type[capacity];
        front = rear = this->size = 0;
    }

    void enqueue(Type value) {
        if (isFull()) {
            std::cout << "Queue is full!" << std::endl;
            return;
        }

        queue[rear++] = value;
        size++;
    }
    Type dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = queue[front++];
        size--;
        return value;
    }
    Type peek() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        return queue[front];
    }
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return rear == capacity - 1;
    }
    int getSize() {
        return size;
    }
    void display() {
        std::cout << "[";
        for (int i = front; i < rear; i++) {
            std::cout << queue[i];
            if (i != rear - 1) std::cout << " <- ";
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class QueueLLB {
   private:
    SinglyLinkedList<Type> list;

   public:
    QueueLLB() {
    }

    void enqueue(Type value) {
        list.insertValue(value);
    }

    Type dequeue() {
        if (list.getSize() < 1) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = list.getHead()->data;
        list.deleteByPosition(1);
        return value;
    }

    Type peek() {
        if (list.getSize() < 1) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = list.getHead()->data;
        return value;
    }

    bool isEmpty() {
        return list.getSize() == 0;
    }

    int getSize() {
        return list.getSize();
    }

    void display() {
        SNode<Type>* head = list.getHead();
        std::cout << "[";
        while (head != nullptr) {
            std::cout << head->data;
            head = head->next;
            if (head != nullptr) std::cout << " <- ";
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class CircularQueue : public QueueAB<Type> {
   public:
    CircularQueue(int size) : QueueAB<Type>(size) {}

    void enqueue(Type value) {
        if (this->size >= this->capacity) {
            std::cout << "Queue is full!" << std::endl;
            return;
        }

        this->rear++;
        if (this->rear >= this->capacity) this->rear = 0;
        this->queue[this->rear] = value;
        this->size++;
    }

    Type dequeue() {
        if (this->size < 1) {
            return Type();
        }

        this->front++;
        if (this->front >= this->capacity) this->front = 0;
        Type value = this->queue[this->front];
        this->size--;
        return value;
    }

    bool isFull() {
        return this->size == this->capacity;
    }

    void display() {
        
    }
};

template <class Type>
class Deque {
};

template <class Type>
class PriorityQueue {
};