#ifndef RAND_H
#define RAND_H

#include <iostream>
#include <random>

class Rand {
    // Add member
    int* arr;
    int size;
    int misses;
    int elNum;
    std::default_random_engine gen;
    std::uniform_int_distribution<int>  dis;

    // You may add private helper functions if you need them

public:
    Rand(int _size) {
        // Constructor
        size=_size;
	arr=new int[_size];
	misses=0;
	elNum=0;
	dis = std::uniform_int_distribution<int>(0,size-1);
    }

    ~Rand() {
        // Destructor
        delete[] arr;
    }

    bool exists(int data) {
        // Return true if data exists in the cache
        // Return false otherwise
        for( int i; i<size; i++)
	{
		if(arr[i]==data)
			return true;
	}
	return false;
    }

    int status() {
        // Return number of elements in cache
        return elNum;
    }

    bool touch(int data) {
	if(exists(data))
	{
		return true;
	}
	else
	{
		if(status()<size)
		{
			arr[elNum]=data;
			this->elNum+=1;
		}
		else
		{
			int index = dis(gen);
			arr[index]=data;
		}
		misses+=1;
		return false;
	}
        // The data is being accessed
        // Return true on hit, false on miss
        // i.e. return true if it existed, and false when it was not
    }

    int get_misses() {
        // Return the number of cache misses until now
        return misses;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            if (arr[i]) {
                std::cout << arr[i] << ' ';
            }
        }
        std::cout << '\n';
    }
};

#endif
