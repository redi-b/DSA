#include <iostream>

#include "stack.h"

using namespace std;

// Using Linked List based stack
bool palindrome(string str);
string decimalToBinary(int num);

// Using Array based stack
string infixToPostfix(string infix);
int evalPostfix(string postfix);

// Helper functions
int evalPrecedence(char op);

int main() {
    // string input;
    // cout << "Enter a string: ";
    // cin >> input;
    // bool isInputPalindrome = palindrome(input);
    // if (isInputPalindrome)
    //     cout << "👍" << endl;
    // else
    //     cout << "👎" << endl;

    // int num;
    // cout << "Enter a number: ";
    // cin >> num;
    // string binary = decimalToBinary(num);
    // cout << num << " in binary: " << binary << endl;

    string infix = "((A + B) - C * (D / E)) + F";
    cout << "Enter an infix expression: ";
    getline(cin, infix);
    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    return 0;
}

bool palindrome(string str) {
    StackLLB<char> stack;

    int strSize = str.length();
    for (int i = 0; i < strSize; i++) {
        stack.push(str[i]);
    }
    for (int i = 0; i < strSize; i++) {
        if (stack.pop() != str[i]) {
            return false;
        }
    }

    return true;
}

string decimalToBinary(int num) {
    StackLLB<int> stack;

    while (num > 0) {
        stack.push(num % 2);
        num /= 2;
    }

    string binary = "";
    while (!stack.isEmpty()) {
        binary += to_string(stack.pop());
    }
    return binary;
}

string infixToPostfix(string infix) {
    string operators = "()^*/+-";
    StackLLB<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == ' ')
            continue;

        if (operators.find(infix[i]) == string::npos) {
            postfix += infix[i];
            continue;
        }

        if (stack.isEmpty() || stack.peek() == '(' || infix[i] == '(') {
            stack.push(infix[i]);
        } else {
            if (infix[i] == ')') {
                while (!stack.isEmpty()) {
                    if (stack.peek() == '(')
                        break;
                    postfix += stack.pop();
                }
                stack.pop();
            } else if (evalPrecedence(infix[i]) > evalPrecedence(stack.peek())) {
                stack.push(infix[i]);
            } else {
                while (evalPrecedence(infix[i]) <= evalPrecedence(stack.peek())) {
                    postfix += stack.pop();
                }
                stack.push(infix[i]);
            }
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

int evalPostfix(string postfix) {
    return 0;
}

int evalPrecedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    if (op == '(' || op == ')')
        return -1;
    return 0;
}
