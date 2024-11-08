#include <string.h>

#include <iostream>
#include <type_traits>
#include <typeinfo>

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

// Trait to check if a type is streamable to cout using <<
template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

template <typename T>
inline constexpr bool is_streamable_v = is_streamable<T>::value;

// Trait to check if a type is comparable using ==
template <typename T, typename = void>
struct is_comparable : std::false_type {};

template <typename T>
struct is_comparable<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

template <typename T>
inline constexpr bool is_comparable_v = is_comparable<T>::value;

// Abstract Linked List Class
template <typename Type>
class LinkedList {
   protected:
    int size;
    std::string strip(const char* str) {
        size_t len = strlen(str);
        if (len <= 7) return str;

        return std::string(str, 7) + "..";
    }

   public:
    virtual void insertValue(Type value, int pos = -1) {
        std::cout << "Function not implemented!" << std::endl;
    }
    virtual void deleteByPosition(int pos) {
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
    void clear() {
        while (this->size > 0) {
            this->deleteByPosition(1);
        }
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

    SinglyLinkedList(std::initializer_list<Type> list) : SinglyLinkedList() {
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
    }

    SinglyLinkedList(SinglyLinkedList<Type>& list) : SinglyLinkedList() {
        SNode<Type>* temp = head;
        while (temp != nullptr) {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        }
    }

    ~SinglyLinkedList() {
        SNode<Type>* temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void insertValue(Type value, int pos = -1) {
        if (pos > (this->size + 1) || (pos <= 0 && pos != -1)) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        SNode<Type>* newNode = new SNode<Type>();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            this->size++;
            return;
        }

        if (pos == 1) {
            newNode->next = head;
            head = newNode;
        } else if (pos == -1 || pos == this->size + 1) {
            SNode<Type>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;

        } else {
            SNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        this->size++;
    }

    void deleteByPosition(int pos) {
        if (this->size == 0) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        if (pos > this->size || pos < 1) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        if (pos == 1) {
            SNode<Type>* temp = head;
            head = head->next;
            delete temp;
        } else {
            SNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            SNode<Type>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
        this->size--;
    }

    void deleteByValue(Type value) {
        int pos = this->search(value);

        if (pos != -1) {
            this->deleteByPosition(pos);
            return;
        }

        std::cout << "Value not found!" << std::endl;
    }

    int search(Type value) {
        if (this->size == 0) return -1;

        int pos = 0;
        SNode<Type>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }

        return -1;
    }

    void print() {
        SNode<Type>* temp = head;
        std::cout << "[";
        while (temp != nullptr) {
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp = temp->next;
            if (temp != nullptr) std::cout << " --> ";
        }
        std::cout << "]" << std::endl;
    }

    void printReverse() {
        if (this->size <= 1) return;
        SNode<Type>* temp1 = nullptr;
        SNode<Type>* temp2 = head;

        while (temp2->next != nullptr) {
            temp1 = temp2;
            temp2 = temp2->next;
        }

        std::cout << "[";
        if constexpr (is_streamable_v<Type>) {
            std::cout << temp2->data << " <-- " << temp1->data;
        } else {
            std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            std::cout << " <-- ";
            std::cout << "<" << this->strip(typeid(Type).name()) << ">";
        }
        SNode<Type>* temp3 = head;
        for (int i = 0; i < this->size - 2; i++) {
            while (temp3->next != temp1) {
                temp3 = temp3->next;
            }
            if constexpr (is_streamable_v<Type>) {
                std::cout << " <-- " << temp3->data;
            } else {
                std::cout << " <-- " << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp2 = temp1;
            temp1 = temp3;
            temp3 = head;
        }
        std::cout << "] - (reverse)" << std::endl;
    }

    SinglyLinkedList<Type>& operator=(std::initializer_list<Type> list) {
        this->clear();
        this->head = nullptr;
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
        return *this;
    }

    SinglyLinkedList<Type>& operator=(SinglyLinkedList<Type>& list) {
        this->clear();
        this->head = nullptr;
        SNode<Type>* temp = list.head;
        while (temp != nullptr) {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        }
        return *this;
    }
};

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

    DoublyLinkedList(std::initializer_list<Type> list) : DoublyLinkedList() {
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
    }

    DoublyLinkedList(DoublyLinkedList<Type>& list) : DoublyLinkedList() {
        SNode<Type>* temp = head;
        while (temp != nullptr) {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        }
    }

    ~DoublyLinkedList() {
        DNode<Type>* temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void insertValue(Type value, int pos = -1) {
        if (pos > (this->size + 1) || (pos <= 0 && pos != -1)) {
            std::cout << "Invalid Position!" << std::endl;
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

        if (pos == 1) {
            DNode<Type>* temp = head;
            newNode->next = temp;
            newNode->prev = nullptr;
            temp->prev = newNode;
            head = newNode;
        } else if (pos == -1 || pos == this->size + 1) {
            DNode<Type>* temp = tail;
            newNode->next = nullptr;
            newNode->prev = temp;
            temp->next = newNode;
            tail = newNode;
        } else {
            DNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next->prev = newNode;
            temp->next = newNode;
            newNode->prev = temp;
        }
        this->size++;
    }

    void deleteByPosition(int pos) {
        if (this->size == 0) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        if (pos > this->size || pos < 1) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        if (pos == 1) {
            DNode<Type>* toDelete = head;
            head = head->next;
            head->prev = nullptr;
            delete toDelete;
        } else if (pos == this->size) {
            DNode<Type>* toDelete = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete toDelete;
        } else {
            DNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
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
        int pos = this->search(value);

        if (pos != -1) {
            this->deleteByPosition(pos);
            return;
        }

        std::cout << "Element not found!" << std::endl;
    }

    int search(Type value) {
        if (this->size == 0) return -1;

        int pos = 1;
        DNode<Type>* temp = head;
        if constexpr (is_comparable_v<Type>) {
            while (temp != nullptr) {
                if (temp->data == value) return pos;
                temp = temp->next;
                pos++;
            }
        } else {
            std::cerr << "Error: Type is not comparable using ==" << std::endl;
        }

        return -1;
    }

    void print() {
        std::cout << "[";
        DNode<Type>* temp = head;
        while (temp != nullptr) {
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
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
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp = temp->prev;
            if (temp != nullptr) std::cout << " <--> ";
        }
        std::cout << "] - (reverse)" << std::endl;
    }

    DoublyLinkedList<Type>& operator=(std::initializer_list<Type> list) {
        this->clear();
        this->head = nullptr;
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
        return *this;
    }

    DoublyLinkedList<Type>& operator=(DoublyLinkedList<Type>& list) {
        this->clear();
        this->head = nullptr;
        SNode<Type>* temp = list.head;
        while (temp != nullptr) {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        }
        return *this;
    }
};

template <typename Type>
class CircularLinkedList : public LinkedList<Type> {
   private:
    SNode<Type>* tail;

    int calculateArrowLen() {
        if (this->size <= 1) return 0;

        int arrowLen = 5 * (this->size - 1);
        int charLen = 0;
        SNode<Type>* temp = tail->next;
        do {
            if constexpr (std::is_same_v<Type, std::string>) {
                charLen += temp->data.length();
            } else if constexpr (std::is_same_v<Type, char*>) {
                charLen += strlen(temp->data);
            } else if constexpr (std::is_arithmetic_v<Type>) {
                charLen += std::to_string(temp->data).length();
            } else {
                charLen += this->strip(typeid(Type).name()).length() + 2;
            }

            temp = temp->next;
        } while (temp != tail->next);

        return arrowLen + charLen - 2;
    }
    void printCircularArrow(int arrowLen, bool reverse = false) {
        if (reverse)
            std::cout << " |";
        else
            std::cout << " +";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << " ";
        }
        if (reverse)
            std::cout << "+" << std::endl;
        else
            std::cout << "|" << std::endl;
        std::cout << " +";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }

   public:
    CircularLinkedList(int size = 0) {
        this->tail = nullptr;
        this->size = size;
    }

    CircularLinkedList(std::initializer_list<Type> list) : CircularLinkedList() {
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
    }

    CircularLinkedList(CircularLinkedList<Type>& list) : CircularLinkedList() {
        SNode<Type>* head = list.tail->next;
        SNode<Type>* temp = head;
        do {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        } while (temp != head);
    }

    ~CircularLinkedList() {
        if (tail == nullptr) return;

        SNode<Type>* head = tail->next;
        SNode<Type>* temp = head;

        do {
            SNode<Type>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);

        tail = nullptr;
    }

    void insertValue(Type value, int pos = -1) {
        if (pos > (this->size + 1) || (pos <= 0 && pos != -1)) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        SNode<Type>* newNode = new SNode<Type>();
        newNode->data = value;
        newNode->next = nullptr;

        SNode<Type>* head = (tail == nullptr || this->size == 1) ? tail : tail->next;

        if (head == nullptr) {
            tail = newNode;
            tail->next = tail;
            this->size++;
            return;
        }

        if (pos == 1) {
            tail->next = newNode;
            newNode->next = head;
        } else if (pos == -1 || pos == this->size + 1) {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        } else {
            SNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        this->size++;
    }

    void deleteByPosition(int pos) {
        if (this->size == 0) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        if (pos > this->size || pos < 1) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        SNode<Type>* head = tail->next;

        if (pos == 1) {
            SNode<Type>* temp = head;
            tail->next = temp->next;
            delete temp;
        } else {
            SNode<Type>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            SNode<Type>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            if (pos == this->size) {
                tail = temp;
            }
        }
        this->size--;
    }

    void deleteByValue(Type value) {
        int pos = this->search(value);

        if (pos != -1) {
            this->deleteByPosition(pos);
            return;
        }

        std::cout << "Element not found!" << std::endl;
    }

    int search(Type value) {
        if (this->size == 0) return -1;

        SNode<Type>* head = tail->next;
        SNode<Type>* temp = head;

        int pos = 1;
        if constexpr (is_comparable_v<Type>) {
            do {
                if (temp->data == value) return pos;
                temp = temp->next;
                pos++;
            } while (temp != head);
        } else {
            std::cerr << "Error: Type is not comparable using ==" << std::endl;
        }

        return -1;
    }

    void print() {
        if (tail == nullptr) {
            std::cout << "[]" << std::endl;
            return;
        }

        SNode<Type>* head = tail->next;
        SNode<Type>* temp = head;

        std::cout << "[";
        do {
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp = temp->next;
            if (temp != head) std::cout << " --> ";
        } while (temp != head);
        std::cout << "]" << std::endl;

        int arrowLen = this->calculateArrowLen();
        if (arrowLen > 0) this->printCircularArrow(arrowLen);
    }

    void printReverse() {
        if (this->size <= 1) return;

        SNode<Type>* head = tail->next;
        SNode<Type>* temp1 = head;
        SNode<Type>* temp2 = head;

        do {
            temp1 = temp2;
            temp2 = temp2->next;
        } while (temp2->next != head);

        SNode<Type>* temp3 = head;
        std::cout << "\n[";
        if constexpr (is_streamable_v<Type>) {
            std::cout << temp2->data << " <-- " << temp1->data;
        } else {
            std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            std::cout << " <-- ";
            std::cout << "<" << this->strip(typeid(Type).name()) << ">";
        }
        for (int i = 0; i < this->size - 2; i++) {
            while (temp3->next != temp1) {
                temp3 = temp3->next;
            }
            if constexpr (is_streamable_v<Type>) {
                std::cout << " <-- " << temp3->data;
            } else {
                std::cout << " <-- " << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp2 = temp1;
            temp1 = temp3;
            temp3 = head;
        }
        std::cout << "] - (reverse)" << std::endl;

        int arrowLen = this->calculateArrowLen();
        if (arrowLen > 0) this->printCircularArrow(arrowLen, true);
    }

    CircularLinkedList<Type>& operator=(std::initializer_list<Type> list) {
        this->clear();
        this->tail = nullptr;
        for (Type value : list) {
            this->insertValue(value, this->size + 1);
        }
        return *this;
    }

    CircularLinkedList<Type>& operator=(CircularLinkedList<Type>& list) {
        this->clear();
        this->tail = nullptr;
        SNode<Type>* head = list.tail->next;
        SNode<Type>* temp = head;
        do {
            this->insertValue(temp->data, this->size + 1);
            temp = temp->next;
        } while (temp != head);

        return *this;
    }
};

// TODO: Implementation
template <typename Type>
class CircularDoublyLinkedList : public LinkedList<Type> {
   private:
    DNode<Type>* head;
    DNode<Type>* tail;

    int calculateArrowLen() {
        if (this->size <= 1) return 0;

        int arrowLen = 6 * (this->size - 1);
        int charLen = 0;
        DNode<Type>* temp = tail->next;
        do {
            if constexpr (std::is_same_v<Type, std::string>) {
                charLen += temp->data.length();
            } else if constexpr (std::is_same_v<Type, char*>) {
                charLen += strlen(temp->data);
            } else if constexpr (std::is_arithmetic_v<Type>) {
                charLen += std::to_string(temp->data).length();
            } else {
                charLen += this->strip(typeid(Type).name()).length() + 2;
            }

            temp = temp->next;
        } while (temp != tail->next);

        return arrowLen + charLen - 2;
    }
    void printCircularArrowTop(int arrowLen, bool reverse = false) {
        if (reverse)
            std::cout << "\n";
        std::cout << " +";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
        if (reverse)
            std::cout << " +";
        else
            std::cout << " |";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << " ";
        }
        if (reverse)
            std::cout << "|" << std::endl;
        else
            std::cout << "+" << std::endl;
    }
    void printCircularArrowBottom(int arrowLen, bool reverse = false) {
        if (reverse)
            std::cout << " |";
        else
            std::cout << " +";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << " ";
        }
        if (reverse)
            std::cout << "+" << std::endl;
        else
            std::cout << "|" << std::endl;
        std::cout << " +";
        for (int i = 0; i < arrowLen; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }

   public:
    CircularDoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    ~CircularDoublyLinkedList() {}

    void insertValue(Type value, int pos = -1) {
        if (pos > (this->size + 1) || (pos <= 0 && pos != -1)) {
            std::cout << "Invalid Position!" << std::endl;
            return;
        }

        DNode<Type>* newNode = new DNode<Type>();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr && tail == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
            tail = head;
            tail->next = head;
            tail->prev = head;
            this->size++;
            return;
        }

        if (pos == 1) {
            newNode->next = head;
            head->prev = newNode;
            tail->next = newNode;
            newNode->prev = tail;
            head = newNode;
        } else if (pos == -1 || pos == (this->size + 1)) {
            tail->next = newNode;
            head->prev = newNode;
            newNode->next = head;
            newNode->prev = tail;
            tail = newNode;
        } else {
            DNode<Type>* temp = head;

            for (int i = 1; i < pos - 1; i++) {
                temp->next = temp;
            }

            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
        }

        this->size++;
    }

    void deleteByPosition(int pos) {}

    void deleteByValue(Type value) {}

    int search(Type value) {
        return -1;
    }

    void print() {
        if (head == nullptr && tail == nullptr) {
            std::cout << "[]" << std::endl;
            return;
        }

        DNode<Type>* temp = head;

        int arrowLen = this->calculateArrowLen();
        if (arrowLen > 0) this->printCircularArrowTop(arrowLen);

        std::cout << "[";
        do {
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp = temp->next;
            if (temp != head) std::cout << " <--> ";
        } while (temp != head);
        std::cout << "]" << std::endl;

        if (arrowLen > 0) this->printCircularArrowBottom(arrowLen);
    }

    void printReverse() {
        if (this->size <= 1) return;

        DNode<Type>* temp = tail;

        int arrowLen = this->calculateArrowLen();
        if (arrowLen > 0) this->printCircularArrowTop(arrowLen, true);

        std::cout << "[";
        do {
            if constexpr (is_streamable_v<Type>) {
                std::cout << temp->data;
            } else {
                std::cout << "<" << this->strip(typeid(Type).name()) << ">";
            }
            temp = temp->prev;
            if (temp != tail) std::cout << " <--> ";
        } while (temp != tail);
        std::cout << "] - (reverse)" << std::endl;

        if (arrowLen > 0) this->printCircularArrowBottom(arrowLen, true);
    }
};
