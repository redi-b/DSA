#include <iostream>

#include "stack.h"

using namespace std;

enum class StackChoice {
    Palindrome,
    DecimalToBinary,
    InfixToPostfix,
    ExpressionEvaluation,
    Exit,
    InvalidChoice
};

enum class ExpChoice {
    Infix,
    Postfix,
    Back,
    InvalidChoice
};

// Using Linked List based stack
bool palindrome(string str);
string decimalToBinary(int num);

// Using Array based stack
string infixToPostfix(string infix);
int evalPostfix(string postfix);

// Helper functions
int evalPrecedence(char op);
StackChoice getStackChoice();
ExpChoice getEvalChoice();
void handleExpEval(ExpChoice expChoice);

int main() {
    StackChoice choice;
    string input;

    do {
        choice = getStackChoice();
        cin.ignore();  // Clear input buffer

        switch (choice) {
            case StackChoice::Palindrome: {
                cout << "Enter a string to check if it's a palindrome: ";
                getline(cin, input);
                bool isInputPalindrome = palindrome(input);
                cout << "Result: " << (isInputPalindrome ? "👍 It's a palindrome!" : "👎 Not a palindrome!") << endl;
                break;
            }

            case StackChoice::DecimalToBinary: {
                int num;
                cout << "Enter a decimal number to convert to binary: ";
                cin >> num;
                string binary = decimalToBinary(num);
                cout << num << " in binary: " << binary << endl;
                break;
            }

            case StackChoice::InfixToPostfix: {
                cout << "Enter an infix expression: ";
                getline(cin, input);
                string postfix = infixToPostfix(input);
                cout << "Postfix expression: " << postfix << endl;
                break;
            }

            case StackChoice::ExpressionEvaluation: {
                ExpChoice expChoice;
                do {
                    expChoice = getEvalChoice();
                    cin.ignore();
                    handleExpEval(expChoice);
                } while (expChoice != ExpChoice::Back);
                break;
            }

            case StackChoice::InvalidChoice:
                cout << "Invalid choice! Please try again." << endl;
                break;

            case StackChoice::Exit:
                cout << "Exiting..." << endl;
                break;
        }

    } while (choice != StackChoice::Exit);

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
    if (num == 0) return "0";

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
    StackALB<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == ' ') continue;

        if (isdigit(infix[i])) {
            postfix += infix[i];
            continue;
        }

        if (stack.isEmpty() || stack.peek() == '(' || infix[i] == '(') {
            stack.push(infix[i]);
        } else {
            if (infix[i] == ')') {
                while (!stack.isEmpty()) {
                    if (stack.peek() == '(') break;
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
    StackALB<int> stack;

    for (int i = 0; i < postfix.length(); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            stack.push(postfix[i] - '0');
        } else {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            switch (postfix[i]) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
                case '^':
                    stack.push(operand1 ^ operand2);
                    break;
            }
        }
    }

    return stack.pop();
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

StackChoice getStackChoice() {
    int choice;
    cout << "\n=======================================" << endl;
    cout << "         Stack Applications            " << endl;
    cout << "=======================================" << endl;
    cout << "1. Check Palindrome" << endl;
    cout << "2. Convert Decimal to Binary" << endl;
    cout << "3. Convert Infix to Postfix" << endl;
    cout << "4. Expression Evaluation" << endl;
    cout << "5. Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return StackChoice::Palindrome;
        case 2:
            return StackChoice::DecimalToBinary;
        case 3:
            return StackChoice::InfixToPostfix;
        case 4:
            return StackChoice::ExpressionEvaluation;
        case 5:
            return StackChoice::Exit;
        default:
            return StackChoice::InvalidChoice;
    }
}

ExpChoice getEvalChoice() {
    int choice;
    cout << "\n=======================================" << endl;
    cout << "      Expression Input Type           " << endl;
    cout << "=======================================" << endl;
    cout << "1. Infix Expression" << endl;
    cout << "2. Postfix Expression" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return ExpChoice::Infix;
        case 2:
            return ExpChoice::Postfix;
        case 3:
            return ExpChoice::Back;
        default:
            return ExpChoice::InvalidChoice;
    }
}

void handleExpEval(ExpChoice expChoice) {
    string input;

    switch (expChoice) {
        case ExpChoice::Infix: {
            cout << "Enter an infix expression: ";
            getline(cin, input);
            string postfix = infixToPostfix(input);
            cout << "Converted to postfix: " << postfix << endl;
            cout << "Evaluation result: " << evalPostfix(postfix) << endl;
            break;
        }

        case ExpChoice::Postfix: {
            cout << "Enter a postfix expression: ";
            getline(cin, input);
            cout << "Evaluation result: " << evalPostfix(input) << endl;
            break;
        }

        case ExpChoice::InvalidChoice:
            cout << "Invalid choice! Please try again." << endl;
            break;

        case ExpChoice::Back:
            break;
    }
}