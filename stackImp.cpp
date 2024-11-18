#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    StackLLB<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(3);
    stack.display();
    stack.pop();
    stack.display();
    stack.pop();
    stack.display();
    stack.pop();
    stack.display();
}
