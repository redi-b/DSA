#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

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
    ~QueueAB() {
        delete[] queue;
    }

    void enqueue(Type value) {
        if (isFull()) {
            std::cout << "Enqueue '" << value << "' failed: Queue is full" << std::endl;
            return;
        }

        queue[rear++] = value;
        size++;
    }

    Type dequeue() {
        if (isEmpty()) {
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
            return Type();
        }

        Type value = queue[front++];
        size--;

        return value;
    }
    Type peek() {
        if (isEmpty()) {
            std::cout << "Peek failed: Queue is empty" << std::endl;
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

    // Overloads with logging
    void enqueue(Type value, bool log) {
        enqueue(value);

        if (log && !isFull()) {
            std::cout << "Enqueue: " << value << std::endl;
            display();
        }
    }
    Type dequeue(bool log) {
        const Type& value = dequeue();

        if (log && !isEmpty()) {
            std::cout << "Dequeue: " << value << std::endl;
            display();
        }

        return value;
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
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
            return Type();
        }

        Type value = queue.getHead()->data;
        queue.deleteByPosition(1);

        return value;
    }

    Type peek() {
        if (queue.getSize() < 1) {
            std::cout << "Peek failed: Queue is empty" << std::endl;
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

    // Overloads with logging
    void enqueue(Type value, bool log) {
        enqueue(value);

        if (log) {
            std::cout << "Enqueue: " << value << std::endl;
            display();
        }
    }

    Type dequeue(bool log) {
        const Type& value = dequeue();

        if (log && !this->isEmpty()) {
            std::cout << "Dequeue: " << value << std::endl;
            display();
        }

        return value;
    }
};

template <class Type>
class CircularQueue : public QueueAB<Type> {
   public:
    CircularQueue(int size) : QueueAB<Type>(size) {}

    void enqueue(Type value) {
        if (isFull()) {
            std::cout << "Enqueue '" << value << "' failed: Queue is full" << std::endl;
            return;
        }

        if (this->rear == this->capacity) this->rear = 0;
        this->queue[this->rear++] = value;
        this->size++;
    }

    Type dequeue() {
        if (this->isEmpty()) {
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
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

    // Overloads with logging
    void enqueue(Type value, bool log) {
        enqueue(value);

        if (log && !isFull()) {
            std::cout << "Enqueue: " << value << std::endl;
            display();
        }
    }

    Type dequeue(bool log) {
        const Type& value = dequeue();

        if (log && !this->isEmpty()) {
            std::cout << "Dequeue: " << value << std::endl;
            display();
        }

        return value;
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
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
            return Type();
        }

        Type value = queue.getHead()->data;
        queue.deleteByPosition(1);

        return value;
    }
    Type dequeueRear() {
        if (isEmpty()) {
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
            return Type();
        }

        Type value = queue.getTail()->data;
        queue.deleteByPosition(queue.getSize());

        return value;
    }
    Type peek() {
        if (isEmpty()) {
            std::cout << "Peek failed: Queue is empty" << std::endl;
            return Type();
        }

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

    // Overloads with logging
    void enqueueFront(Type value, bool log) {
        enqueueFront(value);

        if (log) {
            std::cout << "Enqueue front: " << value << std::endl;
            display();
        }
    }
    void enqueueRear(Type value, bool log) {
        enqueueRear(value);

        if (log) {
            std::cout << "Enqueue rear: " << value << std::endl;
            display();
        }
    }
    Type dequeueFront(bool log) {
        const Type& value = dequeueFront();

        if (log) {
            std::cout << "Dequeue front: " << value << std::endl;
            display();
        }

        return value;
    }
    Type dequeueRear(bool log) {
        const Type& value = dequeueRear();

        if (log) {
            std::cout << "Dequeue rear: " << value << std::endl;
            display();
        }

        return value;
    }
};

template <class DataType>
struct PriorityNode {
    DataType data;
    int priority;
    PriorityNode* next;

    PriorityNode(DataType value, int prio) : data(value), priority(prio), next(nullptr) {}
};

template <class DataType>
class PriorityQueue {
   private:
    using Node = PriorityNode<DataType>;
    Node* front;
    Node* rear;

   public:
    PriorityQueue() : front(nullptr), rear(nullptr) {}

    ~PriorityQueue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(DataType value) {
        Node* newNode = new Node(value, 0);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
        std::cout << "Enqueue: " << newNode->data << " (Priority: " << newNode->priority << ")" << std::endl;
    }

    void enqueue(DataType value, int priority) {
        Node* newNode = new Node(value, priority);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
        std::cout << "Enqueue: " << newNode->data << " (Priority: " << newNode->priority << ")" << std::endl;
    }

    DataType dequeue() {
        if (isEmpty()) {
            std::cout << "Dequeue failed: Queue is empty" << std::endl;
            return DataType();
        }

        Node* prev = nullptr;
        Node* current = front;
        Node* highestPriorityNode = front;
        Node* prevHighest = nullptr;

        // Find the highest priority element
        while (current) {
            if (current->priority > highestPriorityNode->priority) {
                highestPriorityNode = current;
                prevHighest = prev;
            }
            prev = current;
            current = current->next;
        }

        // If the highest priority element is at the front, just dequeue it
        if (highestPriorityNode == front) {
            front = front->next;
            if (!front) rear = nullptr;
        } else {
            // Remove the highest priority node from the queue
            prevHighest->next = highestPriorityNode->next;
            if (highestPriorityNode == rear) {
                rear = prevHighest;
            }
        }

        DataType value = highestPriorityNode->data;
        std::cout << "Dequeue: " << value << " (Priority: " << highestPriorityNode->priority << ")" << std::endl;
        delete highestPriorityNode;
        return value;
    }

    DataType peek() {
        if (isEmpty()) {
            std::cout << "Peek failed: Queue is empty" << std::endl;
            return DataType();
        }

        Node* current = front;
        Node* highestPriorityNode = front;

        // Find the highest priority element
        while (current) {
            if (current->priority > highestPriorityNode->priority) {
                highestPriorityNode = current;
            }
            current = current->next;
        }

        return highestPriorityNode->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void display() {
        Node* current = front;
        std::cout << "[";
        while (current) {
            std::cout << "(" << current->data << ", " << current->priority << ")";
            current = current->next;
            if (current) std::cout << " <- ";
        }
        std::cout << "]\n";
    }
};
