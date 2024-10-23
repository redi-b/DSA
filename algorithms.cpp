#include <iostream>

using namespace std;

enum class MenuChoice { Search,
                        Sort,
                        Exit,
                        Invalid };

enum class SearchChoice { Linear,
                          Binary,
                          Back,
                          Invalid };

enum class SortChoice {
    Simple,
    Bubble,
    Selection,
    Insertion,
    BinaryInsertion,
    Back,
    Invalid
};

// Menu declarations
MenuChoice getMenuChoice();
SearchChoice getSearchChoice();
SortChoice getSortChoice();

// Search algorithm declarations
int linearSearch(int array[], int size);
int binarySearch(int array[], int size);

// Sort algorithm declarations
void simpleSort(int array[], int size);
void bubbleSort(int array[], int size);
void selectionSort(int array[], int size);
void insertionSort(int array[], int size);
void binaryInsertionSort(int array[], int size);

// Helper function declarations
int acceptSize();
void acceptArray(int array[], int size);
void printArray(int array[], int size, string message = "", bool hold = false);

int main(int argc, char const *argv[]) {
    int size = acceptSize();
    int array[size];
    acceptArray(array, size);

    MenuChoice menuChoice;
    do {
        menuChoice = getMenuChoice();

        switch (menuChoice) {
            case MenuChoice::Search:
                SearchChoice searchMenuChoice;
                do {
                    searchMenuChoice = getSearchChoice();

                    switch (searchMenuChoice) {
                        case SearchChoice::Linear:
                            cout << "Linear Search" << endl;
                            printArray(array, size);
                            linearSearch(array, size);
                            break;

                        case SearchChoice::Binary:
                            cout << "Binary Search" << endl;
                            printArray(array, size);
                            binarySearch(array, size);
                            break;

                        case SearchChoice::Back:
                            break;

                        default:
                            cout << "Please enter a valid option!" << endl;
                    }
                } while (searchMenuChoice != SearchChoice::Back);

                break;

            case MenuChoice::Sort:
                SortChoice sortMenuChoice;
                do {
                    sortMenuChoice = getSortChoice();

                    switch (sortMenuChoice) {
                        case SortChoice::Simple:
                            cout << "Simple Sort" << endl;
                            printArray(array, size);
                            simpleSort(array, size);
                            break;

                        case SortChoice::Bubble:
                            cout << "Bubble Sort" << endl;
                            printArray(array, size);
                            bubbleSort(array, size);
                            break;

                        case SortChoice::Selection:
                            cout << "Selection Sort" << endl;
                            printArray(array, size);
                            selectionSort(array, size);
                            break;

                        case SortChoice::Insertion:
                            cout << "Insertion Sort" << endl;
                            printArray(array, size);
                            insertionSort(array, size);
                            break;

                        case SortChoice::BinaryInsertion:
                            cout << "Binary Insertion Sort" << endl;
                            printArray(array, size);
                            binaryInsertionSort(array, size);
                            break;

                        case SortChoice::Back:
                            break;

                        default:
                            cout << "Please enter a valid option!" << endl;
                    }
                } while (sortMenuChoice != SortChoice::Back);

                break;

            case MenuChoice::Exit:
                break;

            default:
                cout << "Please enter a valid option!" << endl;
        }
    } while (menuChoice != MenuChoice::Exit);

    return 0;
}

// ----------- MENU DEFINITIONS -----------

MenuChoice getMenuChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "        Main Menu        " << endl;
    cout << "=========================" << endl;
    cout << "1. Search" << endl;
    cout << "2. Sort" << endl;
    cout << "3. Exit" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return MenuChoice::Search;
        case 2:
            return MenuChoice::Sort;
        case 3:
            return MenuChoice::Exit;
    }

    return MenuChoice::Invalid;
}

SearchChoice getSearchChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "      Search Options      " << endl;
    cout << "=========================" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "3. Back" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return SearchChoice::Linear;
        case 2:
            return SearchChoice::Binary;
        case 3:
            return SearchChoice::Back;
    }

    return SearchChoice::Invalid;
}

SortChoice getSortChoice() {
    int choice;
    cout << "\n=========================" << endl;
    cout << "       Sort Options       " << endl;
    cout << "=========================" << endl;
    cout << "1. Simple Sort" << endl;
    cout << "2. Bubble Sort" << endl;
    cout << "3. Selection Sort" << endl;
    cout << "4. Insertion Sort" << endl;
    cout << "5. Binary Insertion Sort" << endl;
    cout << "6. Back" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return SortChoice::Simple;
        case 2:
            return SortChoice::Bubble;
        case 3:
            return SortChoice::Selection;
        case 4:
            return SortChoice::Insertion;
        case 5:
            return SortChoice::BinaryInsertion;
        case 6:
            return SortChoice::Back;
    }

    return SortChoice::Invalid;
}

// ----------- ALGORITHM DEFINITIONS -----------

int linearSearch(int array[], int size) {
    int searchFor;
    cout << "Enter element to search for: ";
    cin >> searchFor;

    for (int i = 0; i < size; i++) {
        if (array[i] == searchFor) {
            cout << "Element '" << searchFor << "' found at index '" << i << "'"
                 << endl;
            return i;
        }
    }

    cout << "Element not found!" << endl;
    return -1;
}

int binarySearch(int array[], int size) {
    bubbleSort(array, size);

    int searchFor;
    cout << "Enter element to search for: ";
    cin >> searchFor;

    int top = 0;
    int middle = size / 2;
    int bottom = size - 1;

    while (top <= bottom) {
        if (array[middle] == searchFor) {
            cout << "Element '" << searchFor << "' found at index '" << middle
                 << "'" << endl;
            return middle;
        } else if (array[middle] < searchFor) {
            top = middle + 1;
        } else {
            bottom = middle - 1;
        }

        middle = (top + bottom) / 2;
    }

    cout << "Element not found!" << endl;
    return -1;
}

void simpleSort(int array[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printArray(array, size, "Sorted Array: ");
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    printArray(array, size, "Sorted Array: ");
}

void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex])
                minIndex = j;
        }

        if (minIndex != i) {
            int temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }

    printArray(array, size, "Sorted Array: ");
}

void insertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int current = array[i];
        int tail = i - 1;

        while (tail >= 0 && array[tail] > current) {
            array[tail + 1] = array[tail];
            tail--;
        }
        array[tail + 1] = current;
    }

    printArray(array, size, "Sorted Array: ");
}

void binaryInsertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int current = array[i];
        int left = 0;
        int right = i;

        while (left < right) {
            int mid = (left + right) / 2;
            if (array[mid] <= current)
                left = mid + 1;
            else
                right = mid;
        }

        for (int j = i; j > left; j--) {
            array[j] = array[j - 1];
        }
        array[left] = current;
    }

    printArray(array, size, "Sorted Array: ");
}

int acceptSize() {
    cout << endl;
    int size;
    do {
        cout << "Enter size of the array: ";
        cin >> size;
    } while (size <= 0);

    return size;
}

void acceptArray(int array[], int size) {
    int input;
    for (int i = 0; i < size; i++) {
        cout << "Enter array element " << i + 1 << ": ";
        cin >> input;
        array[i] = input;
    }
}

void printArray(int array[], int size, string message, bool hold) {
    if (message.length() > 0)
        cout << message;
    else
        cout << "Array: ";

    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i != size - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    // Pause output so that the user can see the array output
    if (hold)
        system("PAUSE");
}
