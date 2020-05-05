#include<iostream>
#include "lru.h"

int main()
{
	LRU lru(4);
	lru.touch(5);
	lru.touch(0);
	lru.touch(11);
	lru.touch(21);
	lru.print();
	std::cout<<std::endl;
	lru.touch(55);
	std::cout<<std::endl;
	lru.print();
	lru.touch(211);
	std::cout<<std::endl;
	lru.print();
	lru.touch(10);
	std::cout<<std::endl;
	lru.print();
	//lru.touch(41);
	lru.touch(1111);
	lru.touch(112);
	lru.touch(121);
	lru.touch(3);
	lru.touch(2);
	std::cout<<std::endl;
	lru.print();
	return 0;
}

