template <class T>
class ArrayQueue {
    T* _array;
    // You may add member variables.
    int _front; 
    int _size; 
    int capacity;

public:
    ArrayQueue() {
        // Constructor. Initialize member variables, etc
            _front=0;
	    _size=0;
	    capacity=10;
	    _array=new T[capacity];
    }
	
    ~ArrayQueue() {
        // Destructor. Release resources, etc
        delete _array;
    }

    T& front() {
        // Return first element
        return this->_array[_front];
    }


    void pop() {
        // Remove first element
        if(empty())
	{
		return;
	}
	else
	{	
		_front++;
		_size--;
	}

    }


    bool empty() {
        // Return true if empty, false otherwise
        if(this->_size==0)
		return true;
	else
		return false;
    }


    int size() {
        // Return number of elements
        return this->_size;
    }

    void push(T& item) {
        // Add a new item at the end of queue
        if(this->_size==this->capacity)
	{
		this->capacity*=2;
		T* new_array=new T[this->capacity];
		for( int i=0; i<this->_size; i++)
		{
			new_array[i]=this->_array[i];
		}
		new_array[_size]=item;
		delete _array;
		_array=new_array;
	}
	else
	{
		_array[_size]=item;
		
	}
	_size+=1;
    }

    // You may add other member functions
};
