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

    // You may add private helper functions if you need them

public:
    LRU(int _size) {
        // Constructor
    }

    ~LRU() {
        // Destructor
    }

    bool exists(int data) {
        // Return true if data exists in the cache
        // Return false otherwise
    }

    int status() const {
        // Return number of elements in cache
    }

    bool touch(int data) {
        // The data is being accessed
        // Return true on hit, false on miss
        // i.e. return true if it existed, and false when it was not
    }

    int get_misses() {
        // Return the number of cache misses until now
    }

    void print() const {
        bst.print();
        list.print();
    }
};

#endif