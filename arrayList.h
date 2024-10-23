#include <iostream>

using namespace std;

template <typename Type>
class arrayList {
   private:
    int capacity, size;
    Type *array;

    void grow() {
        capacity *= 2;
        Type *newArray = new Type[capacity];

        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    };
    void shrink() {
        capacity /= 2;
        Type *newArray = new Type[capacity];

        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    };

   public:
    arrayList() {
        capacity = 1;
        size = 0;
        array = new Type[capacity];
    };
    ~arrayList() {
        delete[] array;
    };

    void insertValue(Type value, int index = -1) {
        if (size == capacity) grow();

        if (index == -1) {
            array[size] = value;
        } else {
            for (int i = size; i > index; i--) {
                array[i] = array[i - 1];
            }
            array[index] = value;
        }
        size++;
    };

    bool deleteValue(int index) {
        if (size == 0) {
            return false;
        }

        if (index < 0 || index >= size) {
            return false;
        }

        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        size--;

        if (size < capacity / 2) shrink();

        return true;
    };

    Type getValue(int index) {
        if (index < 0 || index >= size) {
            throw invalid_argument("Invalid index!");
        }

        return array[index];
    };

    Type searchValue(Type value) {
        // Linear search
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                return i;
            }
        }

        return -1;
    };

    void sort() {
        // Simple sort
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (array[i] > array[j]) {
                    Type temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    };

    void print() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << array[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]";
        cout << endl;
    };

    int getSize() {
        return size;
    };
};
