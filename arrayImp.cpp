#include <iostream>

#include "arrayList.h"

using namespace std;

enum class MenuChoice {
    Insert,
    Delete,
    Get,
    Search,
    Sort,
    Print,
    Exit,
    InvalidChoice
};

enum class InsertChoice {
    Front,
    Index,
    Back,
    BackToMain,
    InvalidChoice
};

enum class DeleteChoice {
    Front,
    Index,
    Back,
    BackToMain,
    InvalidChoice
};

MenuChoice getMenuChoice();

int main(int argc, char const* argv[]) {
    arrayList list = arrayList<int>();

    MenuChoice menuChoice;
    do {
        menuChoice = getMenuChoice();

        switch (menuChoice) {
            case MenuChoice::Insert: {
                int value;
                cout << "Enter value to insert: ";
                cin >> value;
                list.insertValue(value);
                list.print();
                break;
            }

            case MenuChoice::Delete: {
                int index;
                cout << "Enter index of element to delete: ";
                cin >> index;
                bool deleted = list.deleteValue(index);
                if (deleted) {
                    cout << "Element at index " << index << " deleted." << endl;
                    list.print();
                } else
                    cout << "Element not deleted!";
                break;
            }

            case MenuChoice::Search: {
                int index, element;
                cout << "Enter element to search for: ";
                cin >> element;
                index = list.searchValue(element);
                list.print();
                if (element != -1)
                    cout
                        << "Element '" << element << "' found at index '" << index << "'" << endl;
                else
                    cout << "Element not found!" << endl;
                break;
            }

            case MenuChoice::Sort:
                list.sort();
                list.print();
                break;

            case MenuChoice::Get: {
                int index, element;
                cout << "Enter index of element: ";
                cin >> index;
                try {
                    element = list.getValue(index);
                    cout << "Element at index " << index << " is " << element << endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
                break;
            }

            case MenuChoice::Print:
                list.print();
                break;

            case MenuChoice::Exit:
                break;

            default:
                cout << "Invalid Input!" << endl;
        }
    } while (menuChoice != MenuChoice::Exit);

    return 0;
}

MenuChoice getMenuChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "        Main Menu        " << endl;
    cout << "=========================" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Get Value" << endl;
    cout << "4. Search" << endl;
    cout << "5. Sort" << endl;
    cout << "6. Print" << endl;
    cout << "7. Exit" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return MenuChoice::Insert;
        case 2:
            return MenuChoice::Delete;
        case 3:
            return MenuChoice::Get;
        case 4:
            return MenuChoice::Search;
        case 5:
            return MenuChoice::Sort;
        case 6:
            return MenuChoice::Print;
        case 7:
            return MenuChoice::Exit;
    }

    return MenuChoice::InvalidChoice;
}