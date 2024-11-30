#include <iostream>

#include "queue.h"

using namespace std;

template <template <typename> class Queue, typename Type>
void testQueue(Queue<Type>& queue);

template <typename Type>
void testDeque(Deque<Type>& queue);

int main(int argc, char const *argv[]) {
    QueueAB<int> queueAB(4);
    QueueLLB<int> queueLLB;
    CircularQueue<int> queueCirc(4);
    Deque<int> deque;

    std::cout << "QUEUE TEST\n";
    testQueue(queueLLB);
    // std::cout << "DEQUE TEST\n";
    // testDeque(deque);

    return 0;
}

template <template <typename> class Queue, typename Type>
void testQueue(Queue<Type>& queue) {
    queue.enqueue(4, true);
    queue.enqueue(6, true);
    queue.enqueue(-1, true);
    queue.enqueue(2, true);
    queue.dequeue(true);
    queue.dequeue(true);
    queue.enqueue(18, true);
    queue.enqueue(1, true);
}

template <typename Type>
void testDeque(Deque<Type>& queue) {
    queue.enqueueFront(4, true);
    queue.enqueueFront(6, true);
    queue.enqueueFront(-1, true);
    queue.enqueueFront(2, true);
    queue.dequeueFront(true);
    queue.dequeueFront(true);
    queue.enqueueRear(18, true);
    queue.enqueueRear(1, true);
}