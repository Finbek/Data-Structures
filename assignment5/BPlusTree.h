#ifndef BPlusTree_H
#define BPlusTree_H

#include <iostream>

template <typename T>
struct Node {
    bool is_leaf;
    std::size_t degree;
    T* item;
    Node<T>** children;

public:
    Node(std::size_t degree) {
        // Constructor
        is_leaf = false;
    }
};

template <typename T>
class BPlusTree {
    Node<T>* root;

public:
    BPlusTree(std::size_t degree) {
        // Constructor
    }

    ~BPlusTree() {
        // Destructor
    }

    bool search(T data) {
        // Return true if the item exists. Return false if it does not.
    }

    void insert(T data) {
        // Insert new item into the tree.
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
     * You can assume result_data is safe to use for at least arr_length elements.
     */

    int range_search(T start, T end, T* result_data, int arr_length) {
        // Implement here
    }

    void print(Node<T>* cursor) {
        if (cursor != NULL) {
            for (int i = 0; i < cursor->size; ++i) {
                std::cout << cursor->key[i] << " ";
            }
            std::cout << "\n";

            if (cursor->is_leaf != true) {
                for (int i = 0; i < cursor->size + 1; ++i) {
                    print(cursor->ptr[i]);
                }
            }
        }
    }
};

#endif
