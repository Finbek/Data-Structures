#ifndef LFU_H
#define LFU_H
#include "min_heap.h"

template <typename T>
struct CacheItem {
	int usedCount;  // The number of accesses after inserted to the cache.
	T item;

	explicit CacheItem(T _item = T(), int _usedCount = 0) {
		usedCount = _usedCount;
		item = _item;
	}

	bool operator == (const CacheItem<T> &other) const {
		return item == other.item;
	}

	bool operator < (const CacheItem<T> &other) const {
		return usedCount < other.usedCount;
	}

	bool operator > (const CacheItem<T> &other) const {
		return usedCount > other.usedCount;
	}
};

template <typename T>
class LFU {
	CacheItem<T>* cache;
	const int size;    // cache size
	int misses;
	int elNumb; // number of elements in cache
	// You can add private member variables and functions.

public:
	LFU(int _size) : size(_size) {
		// Constructor
		cache = new CacheItem<T>[_size];
		elNumb=0;
		misses=0; 
	}

	~LFU() {
		// Destructor
		delete[] cache;
	}

	bool exists(T item) {
		// Return true if data exists in the cache
		// Return false otherwise
		for(int i; i<elNumb; i++)
		{	if(cache[i].item==item)
			{ 
				return true;
			}
		}
		return false;
	}

	int status() const {
		// Return number of elements in cache
		return elNumb;
	}

	bool touch(T item) {
		// The data is being accessed
		// Return true on hit, false on miss
		// i.e. return true if it existed, and false when it was not
		
		if(exists(item))
		{	//Find and increase the usedCount by one and heapify again
			for(int i; i<elNumb; i++)
			{
				if(cache[i].item==item)
				{	cache[i].usedCount+=1;
					MinHeap<CacheItem<T>>::make_heap(cache, elNumb, i);
					break;
				}	
			}
			return true;
		}
		else
		{	
			CacheItem<T> * newItem =new CacheItem<T>(item);
			if(size==elNumb)
			{	MinHeap<CacheItem<T>>:: pop(cache, elNumb);
				elNumb-=1;
				MinHeap<CacheItem<T>>:: push(cache, elNumb, *newItem);
				elNumb+=1;
			} 
			else
			{ 
				MinHeap<CacheItem<T>>::push(cache, elNumb, *newItem);
				elNumb+=1;
			}
			misses+=1;
			return false;
		}
		}
	int getMisses() {
		// Return the number of cache misses until now
		return misses;
	}
	int check()
	{
		return size;
	}
};
#endif
