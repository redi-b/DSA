#include <iostream>

#include "arrayList.h"

using namespace std;

#if _WIN32
string clearCommand = "cls";
#else
string clearCommand = "clear";
#endif

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
    BackToMain,
    InvalidChoice
};

MenuChoice getMenuChoice(arrayList<int>& list);
InsertChoice getInsertChoice();
DeleteChoice getDeleteChoice();

int main(int argc, char const* argv[]) {
    system(clearCommand.c_str());

    arrayList<int> list = arrayList<int>();

    MenuChoice menuChoice;
    do {
        menuChoice = getMenuChoice(list);

        switch (menuChoice) {
            case MenuChoice::Insert: {
                InsertChoice insertChoice;
                do {
                    insertChoice = getInsertChoice();
                    switch (insertChoice) {
                        case InsertChoice::Start: {
                            int value;
                            cout << "Enter value to insert: ";
                            cin >> value;
                            list.insertValue(value, 0);
                            list.print();
                        } break;

                        case InsertChoice::Index: {
                            int index, value;
                            cout << "Enter value to insert: ";
                            cin >> value;
                            cout << "Enter index to insert at: ";
                            cin >> index;
                            list.insertValue(value, index);
                            list.print();
                        } break;

                        case InsertChoice::End: {
                            int value;
                            cout << "Enter value to insert: ";
                            cin >> value;
                            list.insertValue(value);
                            list.print();
                        } break;

                        default:
                            break;
                    }
                } while (insertChoice != InsertChoice::BackToMain);

                break;
            }

            case MenuChoice::Delete: {
                DeleteChoice deleteChoice;
                do {
                    deleteChoice = getDeleteChoice();
                    switch (deleteChoice) {
                        case DeleteChoice::Start: {
                            list.deleteValue(0);
                            list.print();
                        } break;

                        case DeleteChoice::Index: {
                            int index;
                            cout << "Enter index to delete at: ";
                            cin >> index;
                            bool deleted = list.deleteValue(index);
                            if (deleted) {
                                cout << "Element deleted successfully!" << endl;
                                list.print();
                            } else
                                cout << "Element not found!" << endl;
                        } break;

                        case DeleteChoice::End: {
                            list.deleteValue(list.getSize() - 1);
                            list.print();
                        } break;

                        default:
                            break;
                    }
                } while (deleteChoice != DeleteChoice::BackToMain);

                break;
            }

            case MenuChoice::Search: {
                int index, element;
                cout << "Enter element to search for: ";
                cin >> element;
                try {
                    index = list.searchValue(element);
                    list.print();
                    cout
                        << "Element '" << element << "' found at index '" << index << "'" << endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
            } break;

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
            } break;

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

MenuChoice getMenuChoice(arrayList<int>& list) {
    cout << "\nArray List Operations" << endl;
    cout << "Array: ";
    list.print();

    int choice;
    cout << "\n=========================" << endl;
    cout << "        Main Menu        " << endl;
    cout << "=========================" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Get Value" << endl;
    cout << "4. Search" << endl;
    cout << "5. Sort" << endl;
    cout << "6. Display" << endl;
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
    cout << "4. Back" << endl;
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
            return DeleteChoice::BackToMain;
    }

    return DeleteChoice::InvalidChoice;
}
