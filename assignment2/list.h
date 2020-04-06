#ifndef LIST_H
#define LIST_H

template <class T>
class Node {
    /*
     * This is a wrapper around 'item', the element we want to store.
     *
     * Template is used to make it work regardless of what type 'T' is.
     * Refer to http://www.cplusplus.com/doc/oldtutorial/templates/ for more info.
     */
public:
    Node* prev;
    Node* next;
    T item;

    Node(T val = T()) {
        prev = nullptr;
        next = nullptr;
        item = val;
    }
};

// Part 1: Implement a doubly linked list.
template <class T>
class LinkedList {
    // Dummy nodes
    Node<T>* head;
    Node<T>* tail;

    // You may add member variables you need.

public:
    LinkedList() {
        // Constructor.
        head = new Node<T>;
        tail = new Node<T>;

        head->prev = nullptr;
        head->next = tail;

        tail->prev = head;
        tail->next = nullptr;

        // Initialize your variables if you added them.
    }

    ~LinkedList() {
        // Destructor.
        clear();
        delete head;
        delete tail;

        // Release yours if you added them.
    }

    // Implement member functions below.
    // Remember: member functions can call each other.

    int size() {
        // Return the number of elements in list.
    }

    bool empty() {
        // Return true if no elements are in list and false otherwise.
    }

    T& front() {
        // Return the front (first) element.
        // Note the return type.
        // It is REFERENCE (not value) of the ITEM (not Node).
    }

    T& back() {
        // Return the back (last) element.
        // Same note as in front().
    }

    void insert(Node<T>* node_before, T val) {
        // Create a node with val. Insert it after node_before.
        // i.e. node_before -> new node -> node_before->next
    }

    void erase(Node<T>* target) {
        // Remove target node from the list.
    }

    void push_front(T val) {
        // Create a node with val. Add it to the front of the list.
    }

    void pop_front() {
        // Remove the front node.
    }

    void push_back(T val) {
        // Create a node with val. Add it to the back of the list.
    }

    void pop_back() {
        // Remove the back node.
    }

    void clear() {
        // Remove all nodes in list.
    }

    Node<T>* find(T val) {
        // Return the pointer of first node with the item val.
    }

    // You may add other member functions.
};

#endif