#include "min_heap.h"
#include "lfu.h"
#include <iostream>

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
/*	int myints[] = { 10, 20, 30, 5, 60 };
	MinHeap<int>::make_heap(myints, 5);
	std::cout << "initial top	:" << myints[0] << std::endl;
	std::cout << "initial top	:" << myints[1] << std::endl;
	std::cout << "initial top	:" << myints[2] << std::endl;
	std::cout << "initial top	:" << myints[3] << std::endl;
	std::cout << "initial top	:" << myints[4] << std::endl;
	std::cout << "initial top	:" << myints[5] << std::endl;
	MinHeap<int>::pop(myints, 5);
	std::cout << "pop	:" << myints[0] << std::endl;
	MinHeap<int>::push(myints, 4, 0);
	std::cout << "push	:" << myints[0] << std::endl;
*/
	// Part2
	LFU<int> lfu(3);
    	std::cout << "lfu: " << lfu.getMisses() << '\n';
	print(lfu.touch(1)); // miss
	print(lfu.touch(2)); // miss
	print(lfu.touch(3)); // miss
	print(lfu.touch(1)); // hit
	std::cout<<lfu.check(0)<<std::endl;
	std::cout<<lfu.check(1)<<std::endl;
	std::cout<<lfu.check(2)<<std::endl;
	print(lfu.touch(2)); // hit
	print(lfu.touch(4)); // miss
	std::cout<<std::endl;
	std::cout<<lfu.check(0)<<std::endl;
	std::cout<<lfu.check(1)<<std::endl;
	std::cout<<lfu.check(2)<<std::endl;
	std::cout<<lfu.getMisses()<<std::endl;
	return 0;
}
