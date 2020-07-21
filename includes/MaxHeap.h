//#ifndef __MAXHEAP_H
//#define __MAXHEAP_H
//
//#include "HeapNode.h"
//
//// @ finish Heap
//
//class MaxHeap
//{
//public:
//	MaxHeap(HeapNode** arr, int size);
//	~MaxHeap();
//
//private:
//	void FixHeap(int key);
//	int Left(int key) const;
//	int Right(int key) const;
//	int Parent(int key) const;
//	void Swap(HeapNode*& p1, HeapNode*& p2);
//
//public:
//	bool IsEmpty() const;
//	void MakeEmpty();
//	void Insert(HeapNode* p);
//	HeapNode* DeleteMax();
//	HeapNode* Max() const;
//
//private:
//	HeapNode** data;
//	int heapSize;
//	int maxSize;
//};
//
//#endif
