#include <iostream>

#include "stack.h"

using namespace std;

enum class StackType {
    ArrayBased,
    ArrayListBased,
    LinkedListBased,
    Exit,
    InvalidChoice
};

enum class MenuChoice {
    Push,
    Pop,
    Peek,
    Display,
    IsEmpty,
    BackToType,
    Exit,
    InvalidChoice
};

StackType getStackType();
MenuChoice getMenuChoice();
template <template <typename> class Stack, typename Type>
void handleStack(Stack<Type>* stack);

int main() {
    while (true) {
        StackType stackType = getStackType();

        switch (stackType) {
            case StackType::ArrayBased: {
                StackAB<int>* stack = new StackAB<int>();
                cout << "Array-based Stack created!" << endl;
                handleStack(stack);
                delete stack;
                break;
            }
            case StackType::ArrayListBased: {
                StackALB<int>* stack = new StackALB<int>();
                cout << "ArrayList-based Stack created!" << endl;
                handleStack(stack);
                delete stack;
                break;
            }
            case StackType::LinkedListBased: {
                StackLLB<int>* stack = new StackLLB<int>();
                cout << "LinkedList-based Stack created!" << endl;
                handleStack(stack);
                delete stack;
                break;
            }
            case StackType::Exit:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

StackType getStackType() {
    int choice;
    cout << "\n=======================================" << endl;
    cout << "         Choose Stack Type            " << endl;
    cout << "=======================================" << endl;
    cout << "1. Array-based Stack" << endl;
    cout << "2. ArrayList-based Stack" << endl;
    cout << "3. LinkedList-based Stack" << endl;
    cout << "4. Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return StackType::ArrayBased;
        case 2:
            return StackType::ArrayListBased;
        case 3:
            return StackType::LinkedListBased;
        case 4:
            return StackType::Exit;
        default:
            return StackType::InvalidChoice;
    }
}

MenuChoice getMenuChoice() {
    int choice;
    cout << "\n=======================================" << endl;
    cout << "            Stack Menu                " << endl;
    cout << "=======================================" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Display" << endl;
    cout << "5. Check if Empty" << endl;
    cout << "6. Back to Stack Type" << endl;
    cout << "7. Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return MenuChoice::Push;
        case 2:
            return MenuChoice::Pop;
        case 3:
            return MenuChoice::Peek;
        case 4:
            return MenuChoice::Display;
        case 5:
            return MenuChoice::IsEmpty;
        case 6:
            return MenuChoice::BackToType;
        case 7:
            return MenuChoice::Exit;
        default:
            return MenuChoice::InvalidChoice;
    }
}

template <template <typename> class Stack, typename Type>
void handleStack(Stack<Type>* stack) {
    MenuChoice choice;
    do {
        choice = getMenuChoice();

        switch (choice) {
            case MenuChoice::Push: {
                Type value;
                cout << "Enter value to push: ";
                cin >> value;
                stack->push(value);
                stack->display();
                break;
            }
            case MenuChoice::Pop: {
                Type value = stack->pop();
                if (!stack->isEmpty()) {
                    cout << "Popped value: " << value << endl;
                }
                stack->display();
                break;
            }
            case MenuChoice::Peek: {
                if (!stack->isEmpty()) {
                    cout << "Top value: " << stack->peek() << endl;
                }
                break;
            }
            case MenuChoice::Display:
                stack->display();
                break;
            case MenuChoice::IsEmpty:
                cout << (stack->isEmpty() ? "Stack is empty" : "Stack is not empty") << endl;
                break;
            case MenuChoice::BackToType:
                return;
            case MenuChoice::Exit:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (true);
}
