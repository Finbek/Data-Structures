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
   
	Node<T>* Parent(Node<T>* cur, Node<T>* child)
	{
		Node<T>* par;
		if(cur->is_leaf or (cur->children[0]->is_leaf))
 			return nullptr;
		for(int i=0; i<cur->size+1; i++)
		{
			if(cur->children[i]!=child)
			{
				par=Parent(cur->children[i], child);
				if(par)
					return par;
			}
					
			else
			{
				par=cur;
					return par;
			
			}
		}
		return par;
	}		

    void InsertIn(T data, Node<T>* cur, Node<T>* child)
	{
		if(cur->size>=degree-1)	
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
		else
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
			if(cur->size>=degree-1)
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
			else	
				inItemInsert(cur, data);
		}
				
    }
     void DeleteInternalRoot(Node<T> * cur, Node<T>* child)
	{
		if(cur->size==1)
                        {
                                if(cur->children[1]==child)
                                {
                                        delete child;
                                        root=cur->children[0];
                                        delete cur;
                                        return;
                                }
                                else if(cur->children[0]==child)
                                {
                                        delete child;
                                        root=cur->children[1];
                                        delete cur;
                                        return;
                                }
                        }
	}
      int indexOfData(Node<T>* cur, T data)
	{
		for(int i=0; i<cur->size; i++)
                {
                        if(cur->item[i]==data)
                                return i;
                }
	}
	int indexOfChild(Node<T>* cur, Node<T>* child)
	{
		for(int i=0; i<cur->size+1; i++)
		{	if(cur->children[i]==child)
				return i;
		}
	}
	void shiftBackItem(Node<T>* cur, int index)
	{
		for(int i=index; i<cur->size+1; i++)
                        cur->item[i]=cur->item[i+1];
	}
	void shiftForwardItem(Node<T>* cur)
	{
		for(int i = cur->size; i>0; i--)
                         cur->item[i]=cur->item[i-1];
	}
	void shiftBackChild(Node<T>* cur, int index)
	{
		for(int i = index; i<cur->size+1; i++)
                        cur->children[i] = cur->children[i+1];
	}
	void shiftForwardChild(Node<T>* cur)
	{
		for(int i = cur->size+1; i>0; i--)
                        cur->children[i]=cur->children[i-1];
	}
	
     void  removeIn(T data, Node<T>* cur, Node<T>* child)
	{
		if(cur!=root){
		int index=indexOfData(cur, data);
		shiftBackItem(cur, index);
		index=indexOfChild(cur, child);
		shiftBackChild(cur, index);
		cur->size--;
		if(cur->size>=degree/2-1 or cur==root)
			return;
		Node<T>* par = Parent(root, cur);
		index=indexOfChild(par, cur);
		int left=index-1;
		int right=index+1;
		if(left>=0)
		{
			Node<T> * lNode = par->children[left];
			if(lNode->size>=degree/2)
			{	shiftForwardItem(cur);
				cur->item[0] = par->item[left];
				par->item[left]=lNode->item[lNode->size-1];
				shiftForwardChild(cur);
				cur->children[0]=lNode->children[lNode->size];
				cur->size++;
				lNode->size--;
				return;
			}
		}
		if(right<=par->size)
		{
			Node<T> * rNode = par->children[right];
			if(rNode->size>=degree/2)
			{
				cur->item[cur->size]=par->item[index];
				par->item[index] = rNode->item[0];
				for(int i=0; i<rNode->size-1; i++)
					rNode->item[i]=rNode->item[i+1];
				cur->children[cur->size+1]=rNode->children[0];
				for(int i = 0; i <rNode->size; ++i)
					rNode->children[i]=rNode->children[i+1];
				cur->size++;
				rNode->size--;
				return;
			}
		}
		if(left>=0)
		{
			Node<T>* lNode = par->children[left];
			lNode->item[lNode->size] = par->item[left];
			for(int i = lNode->size+1, j=0; j<cur->size; j++)
				lNode->item[i] = cur->item[i];
			for(int i = lNode->size+1, j=0; j<cur->size+1;j++)
				{lNode->children[i] = cur->children[j];
				cur->children[j]=nullptr;
				}
			lNode->size+=cur->size+1;
			cur->size=0;
			removeIn(par->item[left], par, cur);
		}
		else if(right<=par->size)
		{
			Node<T> * rNode = par->children[right];
			cur->item[cur->size]=par->item[right-1];
			for(int i = cur->size+1, j=0; j<rNode->size; j++)
				cur->item[i]=rNode->item[j];
			for(int i =cur ->size+1, j=0; j<rNode->size+1; j++)
			{
				cur->children[i]=rNode->children[j];
				rNode->children[j]=nullptr;
			}
			cur->size+= rNode->size+1;
			rNode->size=0;
			removeIn(par->item[right-1], par, rNode);
		}
		}
		else
			DeleteInternalRoot(cur, child);
}
    void DeleteRoot(T data)
	{
		}

    void remove(T data) {
        // Remove an item from the tree.
        if(root)
	{
		Node<T>* cur = root;
		Node<T>* par;
		int left, right;
		while(cur->is_leaf==false)
		{
			for(int i =0; i<cur->size; i++)
			{
				par=cur;
				left=i-1;
				right=i+1;
				if(data<cur->item[i])
				{
					cur=cur->children[i];
					break;
				}
				if(i==cur->size-1)
				{
					left=i;
					right=i+2;
					cur=cur->children[i+1];
					break;
				}
			}
		}
	bool check =search(data);
	if(check)
	{
		int index = indexOfData(cur, data);
		for(int i = index; i<cur->size; i++)
			cur->item[i]=cur->item[i+1];
		cur->size--;
		if(cur==root)
		{
			for(int i = 0; i<degree; i++)
				cur->children[i]=nullptr;
			if(cur->size==0)
			{	
				delete cur;
				root=nullptr;
			}
			return;
		}
		cur->children[cur->size]=cur->children[cur->size+1];
		cur->children[cur->size+1]=nullptr;
		if(cur->size>=degree/2)
			return;
		if(left>=0)
		{
			Node<T>* leftNode = par->children[left];
			if(leftNode->size>=degree/2+1)
			{
				for( int i = cur->size; i>0; i--)
					cur->item[i]=cur->item[i-1];
				cur->size++;
				cur->children[cur->size]=cur->children[cur->size-1];
				cur->children[cur->size-1]=nullptr;
				cur->item[0]=leftNode->item[leftNode->size-1];
				leftNode->size--;
				leftNode->children[leftNode->size]=cur;
				leftNode->children[leftNode->size+1]=nullptr;
				par->item[left]=cur->item[0];
				return;
			}
		}
		if(right<=par->size)
		{
			Node<T>* rightNode = par->children[right];
			if(rightNode->size>=degree/2+1)
			{
				cur->size++;
				cur->children[cur->size]=cur->children[cur->size-1];
				cur->children[cur->size-1]=nullptr;
				cur->item[cur->size-1]=rightNode->item[0];
				rightNode->size--;
				rightNode->children[rightNode->size]=rightNode->children[rightNode->size+1];
				rightNode->children[rightNode->size+1]=nullptr;
				for(int i =0; i<rightNode->size; i++)
					rightNode->item[i]=rightNode->item[i+1];
				par->item[right-1]=rightNode->item[0];
				return;
			}
		}
		if(left>=0)
		{
			Node<T>* lNode = par->children[left];
			for(int i = lNode->size, j =0; j<cur->size; i++, j++)
				lNode->item[i]=cur->item[j];
			lNode->children[lNode->size]=nullptr;
			lNode->size+=cur->size;
			lNode->children[lNode->size]=cur->children[cur->size];
			removeIn(par->item[left], par, cur);
			delete cur;
		}
		else if(right<=par->size)
		{
			Node<T>* rNode=par->children[right];
			for(int i = cur->size, j=0; j<rNode->size; i++, j++)
				cur->item[i] = rNode->item[j];
			cur->children[cur->size]=nullptr;
			cur->size+=rNode->size;
			cur->children[cur->size]=rNode->children[rNode->size];
			removeIn(par->item[right-1], par, rNode);
			delete rNode;
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
