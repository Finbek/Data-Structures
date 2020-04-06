template <class T>
class ArrayStack {
    T* _array;

    // You may add member variables.

public:
    explicit ArrayStack() {
        // Constructor. Initialize member variables, etc.
    }

    ~ArrayStack() {
        // Destructor. Release resources, etc.
    }

    T& top() {
        // Return top element
    }

    void pop() {
        // Remove top element
    }

    bool empty() {
        // Return true if empty, false otherwise
    }

    int size() {
        // Return number of elements
    }

    void push(T& item) {
        // Add a new item at the top
    }

    // You may add other member functions
};