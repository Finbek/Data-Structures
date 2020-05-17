void swap(int *num1, int *num2);


void sort(int* numbers) {
	// implement your sorting algorithm
    // implement your sorting algorithm
    int N=100;
    for (int i=0; i<=N; i++)
    {
        for(int t=i+1; t<=N; t++)
        {
            if(numbers[i]>numbers[t])
                swap(&numbers[i],&numbers[t]);
        }
    }
}

void swap(int *num1, int *num2)
{
    int copy=*num1;
    *num1=*num2;
    *num2=copy;
}
