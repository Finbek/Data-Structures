#include <iostream>
#include "BPlusTree.h"

void print_bool(bool cond) {
    if (cond) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }
}

int main() {
    BPlusTree<int> bpt(3);
    bpt.insert(1);
//std::cout<<bpt.size();
    bpt.insert(2);
    bpt.insert(3);
    bpt.insert(4);
    bpt.insert(5);
    bpt.insert(52);
    bpt.insert(25);
    bpt.insert(351);
    bpt.insert(315);
    bpt.insert(5);

    print_bool(bpt.search(2)); // True
    print_bool(bpt.search(42)); // False

     //bpt.remove(3);
     print_bool(bpt.search(3)); // False
     print_bool(bpt.search(25)); // False
     print_bool(bpt.search(351)); // False
     print_bool(bpt.search(322)); // False
     bpt.remove(42);
    print_bool(bpt.search(42)); // False

    bpt.insert(6);
    bpt.insert(10);

    int* result_array = new int[3];
    int result = bpt.range_search(1, 10, result_array, 3);

    std::cout << result << '\n'; // 3
    for (int i = 0; i < result; i++) {
        std::cout << result_array[i] << ' ';
    }
    std::cout << '\n'; // 5, 6, 10
	
}
