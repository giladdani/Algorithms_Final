#ifndef __MAXHEAP_H
#define __MAXHEAP_H
#include <iostream>
// @ finish Heap
class HeapNode
{
public:
    int key, value;
};
class MaxHeap
{
public:
    MaxHeap(HeapNode *arr, int size);
    ~MaxHeap();

private:
    void FixHeap(int parent_index);
    int Left(int parent_index) const;
    int Right(int parent_index) const;
    int Parent(int child_index) const;
    void Swap(HeapNode &p1, HeapNode &p2);

public:
    bool IsEmpty() const;
    void MakeEmpty();
    void Insert(HeapNode &p);
    HeapNode DeleteMax();
    HeapNode &Max() const;

private:
    HeapNode *data;
    int heapSize;
    int maxSize;
};

#endif
