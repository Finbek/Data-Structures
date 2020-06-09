#ifndef BPlusTree_H
#define BPlusTree_H

#include <iostream>

template <typename T>
struct Node {
    bool is_leaf;
    std::size_t degree; // maximum number of children
    std::size_t size; // current number of children
    T* item;
    Node<T>** children;

    // You may add variables if needed.

public:
    Node(std::size_t degree) {
        // Constructor
        is_leaf = false;
	this->degree=degree;
	this->children= new Node<T>*[degree];
	this->item = new T[degree-1];
	
    }
	~Node(){
	delete [] this->children;
	delete [] this->item;
	}

    // You may add a destructor if needed.
};

template <typename T>
class BPlusTree {
    Node<T>* root;
    std::size_t degree;
public:
    BPlusTree(std::size_t degre) {
        // Constructor
        root= nullptr;
         degree=degre;
    }

    ~BPlusTree() {
        // Destructor
       Deleting(root);
    }


	void inItemInsert(Node<T>* cur, T data)
	{
		int i = 0;
		while(data>cur->item[i] and i<cur->size)
			i++;
		for(int k = cur->size; k>i; k--)
			cur->item[k]=cur->item[k-1];
		cur->item[i]=data;
		cur->size++;
		cur->children[cur->size]=cur->children[cur->size-1];		
		cur->children[cur->size-1]=nullptr;
	}
	
   Node<T>* NodeSearch(Node<T>* cur, T data)
        {
                if(cur->is_leaf)
                {
                        for(int i = 0; i<cur->size; i++)
                        {       if(cur->item[i]==data)
                                        return cur;
                        }
                }
                else
                {
                        for(int i = 0; i<cur->item[i]; i++)
                        {       if(data<cur->item[i])
                                        return NodeSearch(cur->children[i], data);
                                if(i==cur->size-1)
                                        return NodeSearch(cur->children[i+1],data);
                        }
                }
                return nullptr;

   }
        bool search(T data)
        {
                if(NodeSearch(root, data))
                        return true;
                else
                        return false;
        }	
   \
    void insert(T data) {
    }
    void DeleteRoot(T data)
	{
		}

    void remove(T data) {
        // Remove an item from the tree.
        
}
    /* ------ int range_search() ------
     * Find for items with data between start and end, inclusive.
     * result_data is an array with the length of arr_length.
     * If the number of matching data exceeds the length, abort and return -1.
     * Otherwise, fill it with the matching data and return the number of them.
     *
     * For example, if tree is currently [1, 2, 3, 4, 5]
     * and range_search(2, 4, arr, 3) is called,
     * fill arr to make arr == {2, 3, 4} and return 3.
     *
     * You can assume result_data is safe to use for at least arr_length
     * elements.
     */

    int range_search(T start, T end, T* result_data, int arr_length) {
        // Implement here
        int count=arr_length;
        if(root)
	{
		Node<T>* cur=root;
		while(cur->is_leaf==false)
			for(int i = 0; i<cur->size; i++)
			{
				if(start<cur->item[i])
				{	cur=cur->children[i];
					break;
				}
				if(i==cur->size-1)
				{
					cur=cur->children[i+1];
					break;
				}
			}
		while(cur!=nullptr and arr_length>=0)
		
		{	
			for(int i=0; i<cur->size and arr_length>=0; i++)
			{
				if(cur->item[i]>=start and cur->item[i]<=end)
				{	
					result_data[count-arr_length]=cur->item[i];
					arr_length--;
				}
				else
				{	
					return count-arr_length;
				}
			}
			cur=cur->children[cur->size];
		}
		if(arr_length<0)
			return -1;
		else 
			return count-arr_length;
	}
		
}
			
	void Deleting(Node<T>* cur)
	{
		if(cur)
		{
			if(cur->is_leaf==false)
			{
				for(int i = 0; i<cur->size+1; i++)
					{	
							Deleting(cur->children[i]);
					}
			}
			delete cur;
		}
	}
	

    void print(Node<T>* cursor) {
        // You must NOT edit this function.
        if (cursor != NULL) {
            for (int i = 0; i < cursor->size; ++i) {
                std::cout << cursor->item[i] << " ";
            }
            std::cout << "\n";

            if (cursor->is_leaf != true) {
                for (int i = 0; i < cursor->size + 1; ++i) {
                    print(cursor->children[i]);
                }
            }
        }
    }
};

#endif
