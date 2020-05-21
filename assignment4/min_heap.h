#ifndef MIN_HEAP_H
#define MIN_HEAP_H

template <typename T>
struct MinHeap {
	// You can add additional functions
	static void PerlocateDown(T*arr, int size, int index)
	{
		//This function perlocate down the given heap by the provided index, additional function
		//left child index
		int Child=2*index+1;
		T value = arr[index];
		while(Child<size){
			T minValue = value;
			int minIndex = -1;
			for( int i=0; i<2 && i+Child<size; i++)
			{
				if(arr[i+Child]<minValue)
					{
						minValue=arr[i+Child];
						minIndex=i+Child;
					}
			}	
			if(minValue==value)
				return;//the given index has a minimum range
			else {
				swap(&arr[index], &arr[minIndex]);
				index = minIndex;
				Child=2*index+1;			
			}
		}
}  
	static void PerlocateUp(T* arr, int index)
	{
		while(index>0){
			//Index of parent
			int parent = (index-1)/2;
			if(arr[index]<arr[parent])
			{
				swap(&arr[index], &arr[parent]);
				index = parent;
			}
			else 
				return;
		}
	}
	//Swap array item
	static void swap(T* arr1, T* arr2)
	{
		T temp= *arr1;
		*arr1 = *arr2;
		*arr2=temp;

	}

	static void make_heap(T* arr, int size, int hint = -1) {
		// Build heap
		if(hint==-1)
		{
			//heapify
			for(int i = size/2-1; i>=0; i--){
				PerlocateDown(arr, size, i);
			} 
		}
		else{
			//Check whether perlocateUp or PerlocateDown
			int par = (hint-1)/2;
			int child1=hint*2+1;
			int child2=hint*2+2;
			if(size>child2)//checking if there is two children
				{
					if(arr[hint]>arr[child1] || arr[hint]>arr[child2])
						PerlocateDown(arr, size, hint);	
				}
			else if(size>child1)//checking if there is a left child
				{
					if(arr[hint]>arr[child1])
						PerlocateDown(arr,size,hint);
				}
			else if(arr[par]>arr[hint])//checking if parent is bigger than child, so I can perlocate up
			{
				PerlocateUp(arr, hint);
			}
		}
	}

	static void pop(T* arr, int size) {
		// Delete minimum
		arr[0]=arr[size-1];
		PerlocateDown(arr, size-1, 0);
		
	}

	static void push(T*	arr, int size, T item) {
		// Push item
		arr[size]=item;
		PerlocateUp(arr, size);
	}
};	
#endif
