#include <iostream>
#include "queue.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // QueueAB<int> queue(4);
    // QueueLLB<int> queue;
    CircularQueue<int> queue(4);
    queue.enqueue(4);
    queue.enqueue(4);
    cout << queue.peek() << endl;
    return 0;
}
