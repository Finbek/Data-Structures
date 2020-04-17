#include "list.h"

template <class T>
class ListStack {
    LinkedList<T> list;

public:
    T& top() {
        // Return top element
        list.front();
    }

    void pop() {
        // Remove top element
        list.pop_front();
    }

    bool empty() {
        // Return true if empty, false otherwise
        list.empty();
    }

    int size() {
        // Return number of elements
        list.size();
    }

    void push(T& item) {
        // Add a new item at the top
        list.push_front(item);
    }

    // You may add other member functions,
    // including constructor and destructor
};
