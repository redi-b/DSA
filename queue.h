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
        return rear == capacity;
    }
    int getSize() {
        return size;
    }
    void display() {
        std::cout << "[";
        for (int i = front; i < rear; i++) {
            std::cout << queue[i];
            if (i != rear - 1) std::cout << " <-- ";
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class QueueLLB {
   protected:
    SinglyLinkedList<Type> queue;

   public:
    QueueLLB() {}

    void enqueue(Type value) {
        queue.insertValue(value);
    }

    Type dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = queue.getHead()->data;
        queue.deleteByPosition(1);
        return value;
    }

    Type peek() {
        if (queue.getSize() < 1) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = queue.getHead()->data;
        return value;
    }

    bool isEmpty() {
        return queue.getSize() == 0;
    }

    int getSize() {
        return queue.getSize();
    }

    void display() {
        SNode<Type>* head = queue.getHead();
        std::cout << "[";
        while (head != nullptr) {
            std::cout << head->data;
            head = head->next;
            if (head != nullptr) std::cout << " <-- ";
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class CircularQueue : public QueueAB<Type> {
   public:
    CircularQueue(int size) : QueueAB<Type>(size) {}

    void enqueue(Type value) {
        if (isFull()) {
            std::cout << "Queue is full!" << std::endl;
            return;
        }

        if (this->rear == this->capacity) this->rear = 0;
        this->queue[this->rear++] = value;
        this->size++;
    }

    Type dequeue() {
        if (this->isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = this->queue[this->front];
        this->queue[this->front++] = 0;
        if (this->front == this->capacity) this->front = 0;
        this->size--;
        return value;
    }

    bool isFull() {
        return this->size == this->capacity;
    }

    void display() {
        std::cout << "[";
        int idx = this->front;
        for (int i = 0; i < this->size; i++) {
            std::cout << this->queue[idx++];
            if (idx != this->rear) std::cout << " <-- ";
            if (idx == this->capacity) idx = 0;
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class Deque {
   private:
    DoublyLinkedList<Type> queue;

   public:
    Deque() {}

    void enqueueFront(Type value) {
        queue.insertValue(value, 1);
    }
    void enqueueRear(Type value) {
        queue.insertValue(value);
    }
    Type dequeueFront() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = queue.getHead()->data;
        queue.deleteByPosition(1);
        return value;
    }
    Type dequeueRear() {
        if (isEmpty()) {
            std::cout << "Queue is empty!" << std::endl;
            return Type();
        }

        Type value = queue.getTail()->data;
        queue.deleteByPosition(queue.getSize());
        return value;
    }
    Type peek() {
        return queue.getHead()->data;
    }
    bool isEmpty() {
        return queue.getSize() == 0;
    }
    int getSize() {
        return queue.getSize();
    }
    void display() {
        DNode<Type>* head = queue.getHead();
        std::cout << "[";
        while (head != nullptr) {
            std::cout << head->data;
            head = head->next;
            if (head != nullptr) std::cout << " <-- ";
        }
        std::cout << "]" << std::endl;
    }
};

template <class Type>
class PriorityQueue {
};