#include <iostream>
#include <string>

#include "queue.h"

using namespace std;

template <template <typename> class Queue>
void testQueue(Queue<int>& queue);
void testDeque(Deque<int>& queue);
void testPQ(PriorityQueue<int>& queue);

// Helper function
void printTestTitle(string title);

int main(int argc, char const* argv[]) {
    QueueAB<int> queueAB(4);
    QueueLLB<int> queueLLB;
    CircularQueue<int> queueCirc(4);
    Deque<int> deque;
    PriorityQueue<int> priorityQueue;

    printTestTitle("Queue Test");
    testQueue(queueLLB);
    printTestTitle("Deque Test");
    testDeque(deque);
    printTestTitle("Priority Queue Test");
    testPQ(priorityQueue);

    return 0;
}

template <template <typename> class Queue>
void testQueue(Queue<int>& queue) {
    queue.dequeue(true);
    queue.enqueue(4, true);
    queue.enqueue(6, true);
    queue.enqueue(-1, true);
    queue.enqueue(2, true);
    queue.dequeue(true);
    queue.dequeue(true);
    queue.enqueue(18, true);
    queue.enqueue(1, true);
}

void testDeque(Deque<int>& queue) {
    queue.enqueueFront(4, true);
    queue.enqueueFront(6, true);
    queue.enqueueFront(-1, true);
    queue.enqueueFront(2, true);
    queue.dequeueFront(true);
    queue.dequeueFront(true);
    queue.enqueueRear(18, true);
    queue.enqueueRear(1, true);
}

void testPQ(PriorityQueue<int>& queue) {
    queue.enqueue(10, 1);  // Value: 10, Priority: 1
    queue.enqueue(20, 1);  // Value: 20, Priority: 3
    queue.enqueue(30, 2);  // Value: 30, Priority: 2
    queue.enqueue(40, 3);  // Value: 40, Priority: 3
    queue.enqueue(30, 1);  // Value: 30, Priority: 1

    queue.display();
    queue.dequeue();
    queue.display();
}

void printTestTitle(string title) {
    int size = title.size();
    int multiplier = size > 15 ? 2.5 : 3;       // Adjust padding based on title length
    int lineWidth = size * multiplier;          // Total width for the title box
    int padding = (lineWidth - (int)size) / 2;  // Calculate padding on each side

    cout << string(lineWidth, '=') << endl;
    cout << string(padding, ' ') << title << endl; 
    cout << string(lineWidth, '=') << endl;
}