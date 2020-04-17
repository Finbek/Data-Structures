template <class T>
class ArrayStack {
    T* _array;

    // You may add member variables.

public:
    explicit ArrayStack() {
        // Constructor. Initialize member variables, etc.
        int top=0;
	    int capacity=1;
	    _array=new T[capacity];

    }

    ~ArrayStack() {
        // Destructor. Release resources, etc.
        delete _array;
    }

    T& top() {
        // Return top element
        return _array[top];
    }

    void pop() {
        // Remove top element
        if(empty())
    	{
	    	return;
    	}
	    else
	    {
		    top+=1;
    	}

    }

    bool empty() {
        // Return true if empty, false otherwise
        if(this->top==0)
	    	return true;
    	else
		    return false;
    }

    }

    int size() {
        // Return number of elements
        return this->top;
    }

    void push(T& item) {
        // Add a new item at the top
        if(top==capacity)
        {
            capacity*=2;
    		T* new_array=new T[capacity];
	    	for( int i=0; i<top; i++)
		    {
			    new_array[i]=_array[i];
		    }
		    new_array[top]=item;
		    delete _array;
		    _array=new_array;
		    delete new_array;

        }
        else
        {
            _array[top]=item;
        }
        }
        toip+1;
        
    }

    // You may add other member functions
};