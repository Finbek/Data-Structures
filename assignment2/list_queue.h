#include "list.h"

template <class T>
class ListQueue {
    LinkedList<T> list;

public:
    T& front() {
        // Return first element
        list.back();
    }

    void pop() {
        // Remove first element
        list.pop_back();
    }

    bool empty() {
        // Return true if empty, false otherwise
        list.empty();
    }

    int size() {
        // Return number of elements
        list.size();
    }

    void push(T& val) {
        // Add a new item at the end of queue
        list.push_front(val);
    }

    // You may add other member functions,
    // including constructor and destructor
};
