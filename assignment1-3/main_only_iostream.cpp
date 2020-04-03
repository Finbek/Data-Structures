#include <iostream>
#include "sort.h"

void print(int* numbers, int N) {
	for (int i = 0; i < N; ++i) {
		std::cout << numbers[i] << '\n';
	}
}
void quicksort(int *numbers, int First, int Last);
void sort(int* numbers)
{
    int N=sizeof(numbers)-1;
    quicksort (numbers, 0, N);
}



void quicksort(int* numbers, int First, int Last)
{
    if(First>=Last)
    {
        return;
    }
    // implement your sorting algorithm
    int partion=numbers[Last];
    int pivotStartIndex=First;

    for(int k=First; k<=Last; k++)
    {
        if(partion>=numbers[k])
        {
            swap(&numbers[pivotStartIndex], &numbers[k]);
            pivotStartIndex++;
        }
    }
    quicksort(numbers, First, pivotStartIndex-2);
    quicksort(numbers, pivotStartIndex, Last);
}


void swap(int *num1, int *num2)
{
    int copy=*num1;
    *num1=*num2;
    *num2=copy;
}


int main(void) {
    int numbers[] = {65, -20, -48, -75, 59, 89, 79, 29, -82, 75};
    sort(numbers, 10);
    print(numbers, 10);
}

