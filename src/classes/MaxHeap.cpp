//#include "MaxHeap.h"
//
//// Build heap (according to floyd's algorithm)
//MaxHeap::MaxHeap(HeapNode** arr, int size)
//{
//	heapSize = maxSize = size;
//	data = arr;
//
//	for (int i = (size / 2) - 1; i >= 0; i--)	// floyd's algorithm
//		FixHeap(i);
//}
//
//// d'tor
//MaxHeap::~MaxHeap()
//{
//	delete data;
//}
//
//// get index of left child of key in the arr
//int MaxHeap::Left(int key) const
//{
//	return (2 * key + 1);
//}
//
//// get index of right child of key in the arr
//int MaxHeap::Right(int key) const
//{
//	return (2 * key + 2);
//}
//
//// get index of Parent of key in the arr
//int MaxHeap::Parent(int key) const
//{
//	return ((key - 1) / 2);
//}
//
//// Swap
//void MaxHeap::Swap(HeapNode*& p1, HeapNode*& p2)
//{
//	HeapNode* temp = p1;
//	p1 = p2;
//	p2 = temp;
//}
//
//// IsEmpty
//bool MaxHeap::IsEmpty() const
//{
//	if (heapSize == 0)
//		return true;
//	return false;
//}
//
//// MakeEmpty
//void MaxHeap::MakeEmpty()
//{
//	heapSize = 0;
//	delete data;
//}
//
//// DeleteMax
//HeapNode* MaxHeap::DeleteMax()
//{
//	if (heapSize < 1)
//	{
//		cout << "Error: EMPTY HEAP\n";
//		exit(1);
//	}
//
//	HeapNode* max = data[0];
//	heapSize--;
//	data[0] = data[heapSize];
//	FixHeap(0);
//
//	return(max);
//}
//
//// Insert
//void MaxHeap::Insert(HeapNode* p)
//{
//	if (heapSize == maxSize)
//	{
//		cout << "Error: HEAP FULL!\n";
//		exit(1);
//	}
//	int i = heapSize;
//	heapSize++;
//	while ((i > 0) && (data[Parent(i)] < p))
//	{
//		data[i] = data[Parent(i)];
//		i = Parent(i);
//	}
//	data[i] = p;
//}
//
//// Max
//HeapNode* MaxHeap::Max() const
//{
//	return data[0];
//}
//
//// Fix Heap Theta(logn)
//void MaxHeap::FixHeap(int key)
//{
//	int max;
//	int left = Left(key);	// get left child
//	int right = Right(key); // get right child
//
//	if ((left < heapSize) && (*(data[key]) > (*data[left])))
//		max = left;
//	else
//		max = key;
//	if ((right < heapSize) && (*(data[max]) > *(data[right])))
//		max = right;
//
//	if (max != key)
//	{
//		Swap(data[key], data[max]);
//		FixHeap(min);
//	}
//}