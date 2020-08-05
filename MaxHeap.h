#ifndef __MAXHEAP_H
#define __MAXHEAP_H

#include "HeapNode.h"

#define NOT_IN_HEAP -1

class MaxHeap
{
public:
	MaxHeap(HeapNode* arr, int size);
	~MaxHeap();

public:
	void IncreaseKey(int vertex, int newKey);
	int GetIndexInHeap(int vertex) const;
	bool IsEmpty() const;
	void MakeEmpty();
	HeapNode DeleteMax();
	HeapNode& Max() const;

private:
	void Build();
	void FixHeap(int vertex);
	int Parent(int child_index) const;
	int Left(int parent_index) const;
	int Right(int parent_index) const;
	void Swap(HeapNode& p1, HeapNode& p2);

private:
	HeapNode* data;
	int* places;
	int heapSize;
	int maxSize;
};

#endif
