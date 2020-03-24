void swap(int *num1, int *num2);
void sort(int* numbers)
{
    quicksort(<#int *numbers#>, 0,9999)
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

// Add functions if you need to
