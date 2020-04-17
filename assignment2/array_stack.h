template <class T>
class ArrayStack {
    T* _array;
    int _top; 
    int capacity;
    // You may add member variables.

public:
    explicit ArrayStack() {
        // Constructor. Initialize member variables, etc.
        	_top=0;
		capacity=10;
	    	_array=new T[capacity];

    }

    ~ArrayStack() {
        // Destructor. Release resources, etc.
        delete _array;
    }

    T& top() {
        // Return top element
        if(!empty())
	{
		T &ref = _array[_top-1];
		return ref;
	}
    }

    void pop() {
        // Remove top element
        if(empty())
    	{
	    	return;
    	}
        else
	{
		_top-=1;
    	}

    }

    bool empty() {
        // Return true if empty, false otherwise
        if(_top==0)
	    	return true;
    	else
	        return false;
    }

    

    int size() {
        // Return number of elements
        return _top;
    }

    void push(T& item) {
        // Add a new item at the top
        if(_top==capacity)
        {
            capacity*=2;
    		T* new_array=new T[capacity];
	    	for( int i=0; i<_top; i++)
		    {
			    new_array[i]=_array[i];
		    }
		    new_array[_top]=item;
		    delete _array;
		    _array=new_array;

        }
        else
        {
            _array[_top]=item;
        }
       _top+=1;
        
    }

    // You may add other member functions
};
