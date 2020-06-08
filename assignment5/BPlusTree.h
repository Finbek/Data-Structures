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
       
    }

    void traverse(Node<T>* cur, Node<T>* par, T data)
	{
		while(cur->is_leaf==false)
			par=cur;
			for( int i=0; i<cur->size; i++)
			{
				if(data<cur->item[i])
				{
					cur=cur->children[i];
					break;
				}
				if(i==cur->size-1)
				{
					cur=cur->children[i+1];
					break;
				}
			}
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
    bool search(T data) {
        // Return true if the item exists. Return false if it does not.
        if(root)
	{	
		Node<T>* cur = root;
		while(cur->is_leaf==false)
			for(int i =0; i<cur->size; i++)
			{
				if(data<cur->item[i])
				{
					cur=cur->children[i];
					break;
				}
				if(i==cur->size-1)
				{
					cur=cur->children[i+1];
 					break;
				}
			}
		for(int i=0; i<cur->size; i++)
		{	
			if(cur->item[i]==data)
				return true;
		}
		return false;			
	}
		
   }
	Node<T>* Parent(Node<T>* cur, Node<T>* child)
	{
		Node<T>* par;
		if(cur->is_leaf or (cur->children[0]->is_leaf))
 			return nullptr;
		for(int i=0; i<cur->size+1; i++)
		{
			if(cur->children[i]==child)
			{
					par=cur;
					return par;
			}
			else
			{
				par=Parent(cur->children[i], child);
				if(par)
					return par;
			}
		}
		return par;
	}		

    void InsertIn(T data, Node<T>* cur, Node<T>* child)
	{
		if(cur->size<degree-1)
		{
			int i=0;
			while(data>cur->item[i] and i < cur->size)
					i++;
			for(int j = cur->size; j>i; j--)
				cur->item[j]=cur->item[j-1];
			for(int j = cur->size+1; j>i+1; j--)
				cur->children[j]=cur->children[j-1];
			cur->item[i]=data;
			cur->size++;
			cur->children[i+1]=child;
		}
		else
		{
			Node<T>* newNode = new Node<T>(degree);
			T tItem[degree];
			Node<T>* tChild[degree+1];
			for(int i = 0; i<degree-1; i++)
				tItem[i] = cur->item[i];
			for(int i = 0; i<degree; i++)
				tChild[i] = cur->children[i];
			int i = 0;
			while(data>tItem[i] and i<degree-1)
				i++;
			for(int j =degree; j>i; j--)
				tItem[j]=tItem[j-1];
			tItem[i]=data;
			for(int j =degree+1; j>i+1; j--)
				tChild[j]=tChild[j-1];
			tChild[i+1]=child;
			newNode->is_leaf=false;
			cur->size=degree/2;
			newNode->size=degree-1 - cur->size;
			for(int i =0, j =cur->size+1; i<newNode->size; i++, j++)
				newNode->item[i]=tItem[j];
			for(int i =0, j =cur->size+1; i<newNode->size+1; i++, j++)
				newNode->children[i] = tChild[j];
			if(cur==root)
			{
				Node<T> * nRoot = new Node<T>(degree);
				nRoot->item[0] = cur->item[cur->size];
				nRoot->children[0]=cur;
				nRoot->children[1]=newNode;
				nRoot->is_leaf=false;
				nRoot->size=1;
				root = nRoot;
			}
			else
			 	InsertIn(cur->item[cur->size], Parent(root, cur),newNode);
		}
	}	
    void insert(T data) {
        // Insert new item into the tree.
        if(!root)
		{
			root= new Node<T>(degree);
			root->item[0]=data;
			root->is_leaf=true;
			root->size=1;
		}
	else
		{
			Node<T>* cur = root;
			Node<T>* parent;
			while(cur->is_leaf==false)
			{
				parent=cur;
				for(int i = 0; i<cur->size; i++)
				{
					if(data<cur->item[i])
					{
						cur=cur->children[i];
						break;
					}
					if(i==cur->size-1)
					{	
						cur=cur->children[i+1];
						break;
					}
				}	
			}
			if(cur->size<degree-1)
				inItemInsert(cur, data);
			else
			{
				Node<T> * newNode = new Node<T>(degree);
				T temp[degree];
				for(int i=0; i<degree-1; i++)
					temp[i]=cur->item[i];
				int i=0;
				while(data>temp[i] and i<degree-1)
					i++;
				for( int j=degree; j>i; j--)
					temp[j]=temp[j-1];
				temp[i]= data;
				newNode->is_leaf=true;
				cur->size=degree/2;
				newNode->size=degree-cur->size;
				cur->children[cur->size]=newNode;
				newNode->children[newNode->size]=cur->children[degree-1];
				cur->children[degree-1]=nullptr;
				for(int i=0; i<cur->size; i++)
					cur->item[i]=temp[i];
				for(int i=0, j=cur->size; i<newNode->size; i++, j++)
					newNode->item[i]=temp[j];
				if(cur==root)
				{
					Node<T>* nRoot = new Node<T>(degree);
					nRoot->item[0]=newNode->item[0];
					nRoot->children[0]=cur;
					nRoot->children[1]=newNode;
					nRoot->is_leaf=false;
					nRoot->size=1;
					root=nRoot;
				}
				else
					{
						InsertIn(newNode->item[0], parent, newNode);
					}
			}
		}
				
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
			for(int i =0; i<cur->size; i++)
			{
				if(cur->item[i])
					remove(cur->item[i]);
			}
		}
	}
	int  size()
	{
		return root->size;
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
