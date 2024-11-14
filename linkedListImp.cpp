#include <iostream>

#include "linkedList.h"

using namespace std;

#if _WIN32
string clearCommand = "cls";
#else
string clearCommand = "clear";
#endif

enum LinkedListChoice {
    SinglyLinked,
    DoublyLinked,
    CircularLinked,
    CircularDoublyLinked,
    Exit,
    InvalidChoice
};

enum class MenuChoice {
    Insert,
    Delete,
    Search,
    GetSize,
    BackToType,
    Exit,
    InvalidChoice
};

enum class InsertChoice {
    Start,
    Index,
    End,
    BackToMain,
    InvalidChoice
};

enum class DeleteChoice {
    Start,
    Index,
    End,
    Value,
    BackToMain,
    InvalidChoice
};

LinkedListChoice getLinkedListType();
MenuChoice getMenuChoice(LinkedList<int> *list);
InsertChoice getInsertChoice();
DeleteChoice getDeleteChoice();

void insertToList(LinkedList<int> *list);
void deleteFromList(LinkedList<int> *list);

int main() {
    LinkedList<int> *list;

pickType:
    system(clearCommand.c_str());

    // Get the type of linked list from user and initialize the list variable
    LinkedListChoice listType;
    while (true) {
        listType = getLinkedListType();

        if (listType == LinkedListChoice::SinglyLinked) {
            list = new SinglyLinkedList<int>();
            cout << "Singly Linked List Created!" << endl;
            break;
        } else if (listType == LinkedListChoice::DoublyLinked) {
            list = new DoublyLinkedList<int>();
            cout << "Doubly Linked List Created!" << endl;
            break;
        } else if (listType == LinkedListChoice::CircularLinked) {
            list = new CircularLinkedList<int>();
            cout << "Circular Linked List Created!" << endl;
            break;
        } else if (listType == LinkedListChoice::CircularDoublyLinked) {
            list = new CircularDoublyLinkedList<int>();
            cout << "Circular Doubly Linked List Created!" << endl;
            break;
        } else if (listType == LinkedListChoice::Exit) {
            cout << "Exiting..." << endl;
            return 0;
        } else {
            cout << "Invalid Choice!" << endl;
        }
    }

    MenuChoice menuChoice;
    do {
        menuChoice = getMenuChoice(list);

        switch (menuChoice) {
            case MenuChoice::Insert:
                insertToList(list);
                break;

            case MenuChoice::Delete:
                deleteFromList(list);
                break;

            case MenuChoice::Search: {
                int value, pos;
                cout << "Enter element to search for: ";
                cin >> value;
                pos = list->search(value);
                if (pos != -1)
                    cout << "'" << value << "' is found at position '" << pos << "'" << endl;
                else
                    cout << "Element not found!" << endl;
            } break;

            case MenuChoice::GetSize:
                cout << "Size: " << list->getSize() << endl;
                break;
                
            case MenuChoice::BackToType:
                delete list;
                goto pickType;

            case MenuChoice::InvalidChoice:
                cout << "Invalid Choice!" << endl;
                break;
        }
    } while (menuChoice != MenuChoice::Exit);

    cout << "Exiting..." << endl;
    return 0;
}

LinkedListChoice getLinkedListType() {
    int choice;
    cout << "\n=======================================" << endl;
    cout << "    Choose the type of Linked List   " << endl;
    cout << "=======================================" << endl;
    cout << "1. Singly Linked List" << endl;
    cout << "2. Doubly Linked List" << endl;
    cout << "3. Circular Linked List" << endl;
    cout << "4. Circular Doubly Linked List" << endl;
    cout << "5. Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return LinkedListChoice::SinglyLinked;
        case 2:
            return LinkedListChoice::DoublyLinked;
        case 3:
            return LinkedListChoice::CircularLinked;
        case 4:
            return LinkedListChoice::CircularDoublyLinked;
        case 5:
            return LinkedListChoice::Exit;
    }

    return LinkedListChoice::InvalidChoice;
}

MenuChoice getMenuChoice(LinkedList<int> *list) {
    int choice;

    cout << endl;
    list->print();
    list->printReverse();
    cout << "=========================" << endl;
    cout << "        Main Menu        " << endl;
    cout << "=========================" << endl;
    cout << "1. Insert value" << endl;
    cout << "2. Delete value" << endl;
    cout << "3. Search" << endl;
    cout << "4. Get size" << endl;
    cout << "5. Back" << endl;
    cout << "6. Exit" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return MenuChoice::Insert;
        case 2:
            return MenuChoice::Delete;
        case 3:
            return MenuChoice::Search;
        case 4:
            return MenuChoice::GetSize;
        case 5:
            return MenuChoice::BackToType;
        case 6:
            return MenuChoice::Exit;
    }

    return MenuChoice::InvalidChoice;
}

InsertChoice getInsertChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "      Insert Options      " << endl;
    cout << "=========================" << endl;
    cout << "1. Insert at the beginning" << endl;
    cout << "2. Insert at a specific position" << endl;
    cout << "3. Insert at the end" << endl;
    cout << "4. Back" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return InsertChoice::Start;
        case 2:
            return InsertChoice::Index;
        case 3:
            return InsertChoice::End;
        case 4:
            return InsertChoice::BackToMain;
    }

    return InsertChoice::InvalidChoice;
}

DeleteChoice getDeleteChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "      Delete Options      " << endl;
    cout << "=========================" << endl;
    cout << "1. Delete at the beginning" << endl;
    cout << "2. Delete at a specific position" << endl;
    cout << "3. Delete at the end" << endl;
    cout << "4. Delete by value" << endl;
    cout << "5. Back" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return DeleteChoice::Start;
        case 2:
            return DeleteChoice::Index;
        case 3:
            return DeleteChoice::End;
        case 4:
            return DeleteChoice::Value;
        case 5:
            return DeleteChoice::BackToMain;
    }

    return DeleteChoice::InvalidChoice;
}

void insertToList(LinkedList<int> *list) {
    InsertChoice insertChoice;

    do {
        insertChoice = getInsertChoice();
        switch (insertChoice) {
            case InsertChoice::Start: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                list->insertValue(value, 1);
                list->print();
            } break;

            case InsertChoice::Index: {
                int pos, value;
                cout << "Enter position to insert at: ";
                cin >> pos;
                cout << "Enter value to insert: ";
                cin >> value;
                list->insertValue(value, pos);
                list->print();
            } break;

            case InsertChoice::End: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                list->insertValue(value, list->getSize() + 1);
                list->print();
            } break;

            case InsertChoice::InvalidChoice:
                cout << "Invalid Choice!" << endl;
                break;
        }
    } while (insertChoice != InsertChoice::BackToMain);
}

void deleteFromList(LinkedList<int> *list) {
    DeleteChoice deleteChoice;

    do {
        deleteChoice = getDeleteChoice();

        switch (deleteChoice) {
            case DeleteChoice::Start:
                list->deleteByPosition(1);
                list->print();
                break;

            case DeleteChoice::Index: {
                int pos;
                cout << "Enter position to delete at: ";
                cin >> pos;
                list->deleteByPosition(pos);
                list->print();
            } break;

            case DeleteChoice::End:
                list->deleteByPosition(list->getSize());
                list->print();
                break;

            case DeleteChoice::Value: {
                int value;
                cout << "Enter value to delete: ";
                cin >> value;
                list->deleteByValue(value);
                list->print();
            } break;

            case DeleteChoice::InvalidChoice:
                cout << "Invalid Choice!" << endl;
                break;
        }
    } while (deleteChoice != DeleteChoice::BackToMain);
}