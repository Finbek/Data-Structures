#include <iostream>
#include "bst.h"
#include "list.h"
#include "lru.h"
#include "rand.h"
int main()
{	
/*	LinkedList<int> list;
	BinarySearchTree<int, int> bst;
	bst.print();
	bst.insert(30,30);
 	bst.remove(bst.search(30));
	bst.print();
	bst.insert(20,20);
	bst.insert(40,40);
	bst.insert(70,70);
	bst.insert(60,60);
	bst.insert(80,80);
	bst.insert(30,30);
	bst.print();
	bst.clear();
	bst.remove(bst.search(30));
	bst.search(30);
	bst.print();
	bst.insert(40,40);
	bst.insert(60,60);
	bst.print();
	bst.clear();
	bst.print();
	LRU lru(4);
	std::cout<<lru.touch(3)<<'\n';
	lru.touch(2);
	lru.touch(8);
	lru.touch(7);
	std::cout<<lru.get_misses()<<'\n';
	lru.print();
	lru.touch(3);
	lru.touch(1);
	lru.touch(7);
	lru.print();
	std::cout<<lru.exists(2);
	std::cout<<lru.exists(7);
	std::cout<<lru.status();
	std::cout<<lru.exists(9)<<'\n';
	lru.touch(9);
	std::cout<<lru.exists(9)<<'\n';
	std::cout<<lru.get_misses()<<'\n';
	lru.print();*/
	Rand rand(4);
	rand.touch(1);
	rand.touch(6);
	rand.touch(3);
	rand.touch(5);
	rand.touch(2);
	rand.print();
	LRU lru(2);	
	for( int i; i<1000000; ++i)
		lru.touch(i%200);
	lru.print();
	return 0;
}
