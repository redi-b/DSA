template <typename Type>
struct Node {
    Type data;
    Node* next;
};

template <typename Type>
class SinglyLinkedList {
   private:
    Node<Type>* head;
    int size;

   public:
    SinglyLinkedList(int size = 0) {
        this->head = nullptr;
        this->size = size;
    }

    ~SinglyLinkedList() {
        Node<Type>* temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void insertValue(Type value, int index = -1) {
        Node<Type>* newNode = new Node<Type>();
        newNode->data = value;
        newNode->next = nullptr;

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else if (index == -1) {
            if (head == nullptr) {
                head = newNode;
            } else {
                Node<Type>* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        } else {
            Node<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                if (temp == nullptr) {
                    std::cout << "Index out of range!" << std::endl;
                    return;
                }
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    void deleteByIndex(int index) {
        if (index == 0) {
            Node<Type>* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node<Type>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                if (temp == nullptr) {
                    std::cout << "Index out of range!" << std::endl;
                    return;
                }
                temp = temp->next;
            }
            Node<Type>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
        size--;
    }

    void deleteByValue(Type value) {
        Node<Type>* temp = head;
        if (temp->data == value) {
            head = head->next;
            delete temp;
            size--;
            return;
        }
        while (temp->next != nullptr) {
            if (temp->next->data == value) {
                Node<Type>* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
                size--;
                return;
            }
            temp = temp->next;
        }
        std::cout << "Value not found!" << std::endl;
    }

    void print() {
        Node<Type>* temp = head;
        std::cout << "[";
        while (temp != nullptr) {
            std::cout << temp->data;
            temp = temp->next;
            if (temp != nullptr) std::cout << " --> ";
        }
        std::cout << "]" << std::endl;
    }
};