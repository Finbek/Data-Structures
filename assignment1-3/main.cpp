#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "sort.h"
#include <time.h>
#define N 10000000

void print(int* numbers) {
	for (int i = 0; i < N; ++i) {
		std::cout << numbers[i] << '\n';
	}
}

int compareWithAnswer(int* arr, int* arr_answer) {
	for (int i = 0; i < N; i++) {
		if (arr[i] != arr_answer[i])
			
			return 0;
	}
	return 1;
}

int main(void) {
	time_t start, end;
	double cpu_time_used;
	int* arr;
	int* arr_answer;
	bool result;
	start=clock();
	arr = (int*)malloc(sizeof(int) * N);
	arr_answer = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		arr_answer[i] = i + 1;
		arr[i] = i + 1;
	}

	std::random_shuffle(arr, arr + N);

	sort(arr, N); // you should implement this function
        
	result = compareWithAnswer(arr, arr_answer);
	end=clock();
	cpu_time_used=(double(end-start))/CLOCKS_PER_SEC;
	std::cout<<result << std::endl;
	std::cout<<cpu_time_used<<std::endl;

	free(arr);
	free(arr_answer);

	return result;
}
