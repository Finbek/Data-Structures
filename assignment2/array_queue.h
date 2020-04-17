template <class T>
class ArrayQueue {
    T* _array;
    // You may add member variables.

public:
    ArrayQueue() {
        // Constructor. Initialize member variables, etc
        int front=0;
	    int size=0;
	    int capacity=1;
	_array=new T[capacity];
    }
	
    ~ArrayQueue() {
        // Destructor. Release resources, etc
        delete _array;
    }

    T& front() {
        // Return first element
        return this->_array[size-1];
    }


    void pop() {
        // Remove first element
        if(empty())
	{
		return;
	}
	else if(back==front)
	{
		front=size=0;
	}
	else
	{
		front+=1;
	}

    }


    bool empty() {
        // Return true if empty, false otherwise
        if(this->size==0)
		return true;
	else
		return false;
    }


    int size() {
        // Return number of elements
        return this-> size;
    }

    void push(T& item) {
        // Add a new item at the end of queue
        if(size==capacity)
	{
		capacity*=2;
		T* new_array=new T[capacity];
		for( int i=0; i<size; i++)
		{
			new_array[i]=_array[i];
		}
		new_array[size]=item;
		delete _array;
		_array=new_array;
		delete new_array;
	}
	else
	{
		_array[size]=item;
		
	}
	size+=1;
    }

    // You may add other member functions
};
