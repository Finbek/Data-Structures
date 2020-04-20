#ifndef RAND_H
#define RAND_H

#include <iostream>
#include <random>

class Rand {
    // Add member
    int** arr;
    int size;
    int misses;

    std::default_random_engine gen;
    std::uniform_int_distribution<int>* dis;

    // You may add private helper functions if you need them

public:
    Rand(int _size) {
        // Constructor
    }

    ~Rand() {
        // Destructor
    }

    bool exists(int data) {
        // Return true if data exists in the cache
        // Return false otherwise
    }

    int status() {
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
        for (int i = 0; i < size; i++) {
            if (arr[i] != nullptr) {
                std::cout << *arr[i] << ' ';
            }
        }
        std::cout << '\n';
    }
};

#endif