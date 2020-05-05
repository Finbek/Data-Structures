#ifndef LRU_H
#define LRU_H

#include <iostream>
#include "bst.h"
#include "list.h"

struct LRU_Unit {
    int value;
    TreeNode<int, Node<LRU_Unit>*>* tn;

    LRU_Unit(int val = int(), TreeNode<int, Node<LRU_Unit>*>* _tn = nullptr) {
        value = val;
        tn = _tn;
    }
};

class LRU {
    BinarySearchTree<int, Node<LRU_Unit>*> bst;
    LinkedList<LRU_Unit> list;
    int size;
    int misses;
    int elNum;

    // You may add private helper functions if you need them

public:
    LRU(int _size) {
        // Constructor
        size=_size; 
	misses=0;
	elNum=0;
//	list= new LinkedList<LRU_Unit>;
//	bst = new BinarySearchTree<int, Node<LRU_Unit>*>; 
    }

    ~LRU() {
        // Destructor
        //delete *size;
	//delete *misses;
//	delete list;
//	delete bst; 
    }

    bool exists(int data) {
        // Return true if data exists in the cache
        // Return false otherwise
        //
        if(bst.search(data))
		return true;
	else 
		return false;
    }

    int status() const {
        // Return number of elements in cache
        return elNum;
    }

    bool touch(int data) {
        // The data is being accessed
        // Return true on hit, false on miss
        // i.e. return true if it existed, and false when it was not
	
        LRU_Unit* unit = new LRU_Unit(data, nullptr);
	if(exists(data))
	{	
		TreeNode<int, Node<LRU_Unit>*>* _tn = bst.search(data);	
		list.erase(_tn->val);
		delete _tn->val;
		bst.remove(_tn);
		Node<LRU_Unit>* node = list.push_back(*unit);
		TreeNode<int, Node<LRU_Unit>*>* _tnz = bst.insert(data, node);
		node->item.tn=_tnz;
		return true;
	}
	else
	{	
		if(status()<size)
		{	
			Node<LRU_Unit> * node = list.push_back(*unit);
			TreeNode<int, Node<LRU_Unit>*>* _tn = bst.insert(data, node);
			node->item.tn=_tn;
			elNum+=1;
		}
		else
		{
			Node<LRU_Unit> * node = list.front();
			bst.remove(node->item.tn);	
			list.pop_front();
			node = list.push_back(*unit);	
			TreeNode<int, Node<LRU_Unit>*>* _tn = bst.insert(data, node);
			node->item.tn=_tn;
		}
		misses+=1;
		return false;
	}

    }
		
    int get_misses() {
        // Return the number of cache misses until now
        return misses; 
    }

    void print() const {
        bst.print();
        list.print();
    }
};

#endif
