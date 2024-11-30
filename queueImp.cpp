#include <iostream>
#include "queue.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // QueueAB<int> queue(4);
    // QueueLLB<int> queue;
    // CircularQueue<int> queue(4);
    Deque<int> queue;
    queue.enqueueFront(4);
    queue.display();
    queue.enqueueFront(6);
    queue.display();
    queue.enqueueFront(-1);
    queue.display();
    queue.enqueueFront(2);
    queue.display();
    queue.dequeueFront();
    queue.display();
    queue.dequeueFront();
    queue.display();
    queue.enqueueRear(18);
    queue.display();
    queue.enqueueRear(1);
    queue.display();
    return 0;
}
