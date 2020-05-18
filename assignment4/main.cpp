
#include <iostream>
#include "min_heap.h"

void print(bool result) {
	if (result) {
		std::cout << "hit\n";
	}
	else {
		std::cout << "miss\n";
	}
}

int main(void) {
	// Part1
	int myints[] = { 10, 20, 30, 5, 60 };

	MinHeap<int>::make_heap(myints, 5);
	std::cout << "initial top	:" << myints[0] << std::endl;
	MinHeap<int>::pop(myints, 5);
	std::cout << "pop	:" << myints[0] << std::endl;
	MinHeap<int>::push(myints, 4, 2);
	std::cout << "push	:" << myints[0] << std::endl;
/*
	// Part2
	LFU<int> lfu(3);

	print(lfu.touch(1)); // miss
	print(lfu.touch(2)); // miss
	print(lfu.touch(3)); // miss
	print(lfu.touch(1)); // hit
	print(lfu.touch(2)); // hit
	print(lfu.touch(4)); // miss
*/
	return 0;

}
