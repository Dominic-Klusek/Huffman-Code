#include"MinHeap.h"

template <class T>
MinHeap<T>& MinHeap<T>::Insert(T& x)
{	
	if (Size == MaxSize)
		throw 152;
	else
	{
		int i = ++Size;
		while (i != 1 && x.frequency < heap[i / 2].frequency)
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = x;
		return *this;
	}
}

template <class T>
MinHeap<T>& MinHeap<T>::Delete(T& x)
{
	if (Size == 0)
		throw 55;
	x = heap[1];  //root has the smallest key
	T y = heap[Size--]; //last element
	int vacant = 1;
	int child = 2; //make child = left child
	while (child <= Size)
	{
		if (child < Size && heap[child].frequency > heap[child + 1].frequency)
			++child;
		//right child < left child
		if (y.frequency <= heap[child].frequency)
			break;
		heap[vacant] = heap[child]; //move smaller child
		vacant = child; //new vacant
		child = child * 2; // new child of vacant
	}
	heap[vacant] = y;
	return *this;
}

/*if (Size == MaxSize)
		throw 152;
	else
	{
		int i = ++Size;
		while (i != 1 && x.frequency > heap[i / 2].frequency)
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = x;
		return *this;
	}*/
/*
if (Size == 0)
		throw 55;

	x = heap[1];  //root has the smallest key

	T y = heap[Size--]; //last element

	int vacant = 1;
	int child = 2; //make child = left child

	while (child <= Size)
	{
		if (child < Size && heap[child].frequency < heap[child + 1].frequency)
			++child;
		//right child < left child
		if (y.frequency >= heap[child].frequency)
			break;
		heap[vacant] = heap[child]; //move smaller child
		vacant = child; //new vacant
		child = child * 2; // new child of vacant
	}
	heap[vacant] = y;
	return *this;
*/