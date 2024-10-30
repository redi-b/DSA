#include <iostream>

template <typename Type>
struct SNode {
    Type data;
    SNode* next;
};

template <typename Type>
struct DNode {
    Type data;
    DNode* next;
    DNode* prev;
};

// Abstract Linked List Class
template <typename Type>
class LinkedList {
   protected:
    int size;

   public:
    virtual void insertValue(Type value, int index = -1) {
        std::cout << "Function not implemented!" << std::endl;
    }
    virtual void deleteByIndex(int index) {
        std::cout << "Function not implemented!" << std::endl;
    }
    virtual void deleteByValue(int value) {
        std::cout << "Function not implemented!" << std::endl;
    };
    virtual int search(Type value) {
        return -1;
    };
    virtual void print() {
        std::cout << "[]" << std::endl;
    }
    virtual void printReverse() {}

    int getSize() {
        return size;
    }
};

template <typename Type>
class SinglyLinkedList : public LinkedList<Type> {
   private:
    SNode<Type>* head;

   public:
    SinglyLinkedList(int size = 0) {
        this->head = nullptr;
        this->size = size;
    }

    ~SinglyLinkedList() {
        SNode<Type>* temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void insertValue(Type value, int index = -1) {
        if (index > this->size || index < -1) {
            std::cout << "Index out of bounds!" << std::endl;
            return;
        }

        SNode<Type>* newNode = new SNode<Type>();
        newNode->data = value;
        newNode->next = nullptr;

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else if (index == -1 || index == this->size) {
            if (head == nullptr) {
                head = newNode;
            } else {
                SNode<Type>* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        } else {
            SNode<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        this->size++;
    }

    void deleteByIndex(int index) {
        if (this->size == 0) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        if (index >= this->size || index < 0) {
            std::cout << "Index out of bounds!" << std::endl;
            return;
        }

        if (index == 0) {
            SNode<Type>* temp = head;
            head = head->next;
            delete temp;
        } else {
            SNode<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            SNode<Type>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
        this->size--;
    }

    void deleteByValue(Type value) {
        int index = this->search(value);

        if (index != -1) {
            this->deleteByIndex(index);
            return;
        }

        std::cout << "Value not found!" << std::endl;
    }

    int search(Type value) {
        if (this->size == 0) return -1;

        int index = 0;
        SNode<Type>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) return index;
            temp = temp->next;
            index++;
        }

        return -1;
    }

    void print() {
        SNode<Type>* temp = head;
        std::cout << "[";
        while (temp != nullptr) {
            std::cout << temp->data;
            temp = temp->next;
            if (temp != nullptr) std::cout << " --> ";
        }
        std::cout << "]" << std::endl;
    }
};

// TODO: Implementation
template <typename Type>
class DoublyLinkedList : public LinkedList<Type> {
   private:
    DNode<Type>* head;
    DNode<Type>* tail;

   public:
    DoublyLinkedList(int size = 0) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = size;
    }
    ~DoublyLinkedList() {
        DNode<Type>* temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void insertValue(Type value, int index = -1) {
        if (index > this->size || index < -1) {
            std::cout << "Index out of bounds!" << std::endl;
            return;
        }

        DNode<Type>* newNode = new DNode<Type>();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr && tail == nullptr) {
            head = newNode;
            tail = newNode;
            this->size++;
            return;
        }

        if (index == 0) {
            DNode<Type>* temp = head;
            newNode->next = temp;
            newNode->prev = nullptr;
            temp->prev = newNode;
            head = newNode;
        } else if (index == -1 || index == this->size) {
            DNode<Type>* temp = tail;
            newNode->next = nullptr;
            newNode->prev = temp;
            temp->next = newNode;
            tail = newNode;
        } else {
            DNode<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next->prev = newNode;
            temp->next = newNode;
            newNode->prev = temp;
        }
        this->size++;
    }

    void deleteByIndex(int index) {
        if (index >= this->size || index < 0) {
            std::cout << "Index out of bounds!" << std::endl;
            return;
        }

        if (index == 0) {
            DNode<Type>* toDelete = head;
            head = head->next;
            head->prev = nullptr;
            delete toDelete;
        } else if (index == this->size - 1) {
            DNode<Type>* toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete toDelete;
        } else {
            DNode<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            DNode<Type>* toDelete = temp->next;
            toDelete->next->prev = temp;
            temp->next = toDelete->next;
            delete toDelete;
        }
        this->size--;
    }

    void deleteByValue(Type value) {
        int index = this->search(value);

        if (index != -1) {
            this->deleteByIndex(index);
            return;
        }

        std::cout << "Element not found!" << std::endl;
    }

    int search(Type value) {
        if (this->size == 0) return -1;

        int index = 0;
        DNode<Type>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) return index;
            temp = temp->next;
            index++;
        }

        return -1;
    }

    void print() {
        std::cout << "[";
        DNode<Type>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data;
            temp = temp->next;
            if (temp != nullptr) std::cout << " <--> ";
        }
        std::cout << "]" << std::endl;
    }

    void printReverse() {
        if (this->size <= 1) return;
        std::cout << "[";
        DNode<Type>* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data;
            temp = temp->prev;
            if (temp != nullptr) std::cout << " <--> ";
        }
        std::cout << "] - (reverse)" << std::endl;
    }
};

// TODO: Implementation
template <typename Type>
class CircularLinkedList : public LinkedList<Type> {
   private:
    SNode<Type>* head;

   public:
    CircularLinkedList() {}
    ~CircularLinkedList() {}
};

// TODO: Implementation
template <typename Type>
class CircularDoublyLinkedList : public LinkedList<Type> {
   private:
    DNode<Type>* head;
    DNode<Type>* tail;

   public:
    CircularDoublyLinkedList() {}
    ~CircularDoublyLinkedList() {}
};
