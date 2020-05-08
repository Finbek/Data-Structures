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

	// You can add private member variables and functions.

public:
	LFU(int _size) : size(_size) {
		// Constructor
	}

	~LFU() {
		// Destructor
	}

	bool exists(T item) {
		// Return true if data exists in the cache
		// Return false otherwise
	}

	int status() const {
		// Return number of elements in cache
	}

	bool touch(T item) {
		// The data is being accessed
		// Return true on hit, false on miss
		// i.e. return true if it existed, and false when it was not
	}

	int getMisses() {
		// Return the number of cache misses until now
	}
};
#endif