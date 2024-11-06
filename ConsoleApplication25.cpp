#include <iostream>

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
    }

public:
    Stack(int initialCapacity = 10) : top(nullptr), size(0), capacity(initialCapacity) {}

    ~Stack() {
        while (top) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        if (size >= capacity) {
            resize();
        }
        Node* newNode = new Node{ value, top };
        top = newNode;
        size++;
    }

    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack underflow\n";
            return -1;
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            std::cerr << "Stack is empty\n";
            return -1;
        }
        return top->data;
    }

    int getSize() const {
        return size;
    }
};
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(int value) {
        Node* newNode = new Node{ value, head };
        head = newNode;
    }

    LinkedList clone() const {
        LinkedList newList;
        Node* current = head;
        Node* tail = nullptr;
        while (current) {
            Node* newNode = new Node{ current->data, nullptr };
            if (tail) {
                tail->next = newNode;
            }
            else {
                newList.head = newNode;
            }
            tail = newNode;
            current = current->next;
        }
        return newList;
    }

    LinkedList operator+(const LinkedList& other) const {
        LinkedList newList = clone();
        Node* current = newList.head;
        if (!current) {
            newList.head = other.clone().head;
            return newList;
        }
        while (current->next) {
            current = current->next;
        }
        current->next = other.clone().head;
        return newList;
    }

    LinkedList operator*(const LinkedList& other) const {
        LinkedList newList;
        Node* current = head;
        while (current) {
            if (other.contains(current->data)) {
                newList.add(current->data);
            }
            current = current->next;
        }
        return newList;
    }

    bool contains(int value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }
};

int main() {
   
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Top of stack: " << stack.peek() << "\n";
    stack.pop();
    std::cout << "Top after pop: " << stack.peek() << "\n";

    LinkedList list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    LinkedList list2;
    list2.add(3);
    list2.add(4);
    list2.add(5);

    LinkedList clonedList = list1.clone();
    std::cout << "Cloned list: ";
    clonedList.display();

    LinkedList mergedList = list1 + list2;
    std::cout << "Merged list: ";
    mergedList.display();

    LinkedList commonElementsList = list1 * list2;
    std::cout << "Common elements list: ";
    commonElementsList.display();

    return 0;
}
