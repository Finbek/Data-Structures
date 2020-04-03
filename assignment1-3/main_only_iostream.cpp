#include <iostream>
#include "sort.h"

void print(int* numbers, int N) {
	for (int i = 0; i < N; ++i) {
		std::cout << numbers[i] << '\n';
	}
}

int main(void) {
    int numbers[] = {65, -20, -48, -75, 59, 89, 79, 29, -82, 75};
    sort(numbers, 10);
    print(numbers, 10);
}
