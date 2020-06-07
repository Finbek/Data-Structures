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
    }

    ~LRU() {
	bst.clear();        
	list.clear();
    }

    bool exists(int data) {
        // Return true if data exists in the cache
        // Return false otherwise
        //
        if(bst.search(data)==nullptr)
		return false;
	else 
		return true;
    }

    int status() const {
        // Return number of elements in cache
	return elNum;    	
}

    bool touch(int data) {
        // The data is being accessed
        // Return true on hit, false on miss
        // i.e. return true if it existed, and false when it was not
	if(exists(data))
	{	
		TreeNode<int, Node<LRU_Unit>*>* _tn = bst.search(data);	
		Node<LRU_Unit>* target= _tn->val;
		list.erase(target);
		delete target;
		list.push_back(_tn->val->item);
		return true;
	}
	else
	{	
        	LRU_Unit* unit = new LRU_Unit(data, nullptr);
		if(status()<size)
		{	
			Node<LRU_Unit> * node = list.push_back(*unit);
			TreeNode<int, Node<LRU_Unit>*>* _tn = bst.insert(data, node);
			node->item.tn=_tn;
			elNum+=1;
		}
		else
		{
			LRU_Unit  u = list.front();
			bst.remove(bst.search(u.value));	
			list.pop_front();
			Node<LRU_Unit> *node = list.push_back(*unit);	
			TreeNode<int, Node<LRU_Unit>*>* _tn = bst.insert(data, node);
			node->item.tn=_tn;
		}
		delete unit;
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
