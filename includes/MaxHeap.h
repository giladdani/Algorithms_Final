#ifndef __MAXHEAP_H
#define __MAXHEAP_H
#include <iostream>
// @ finish Heap
class HeapNode
{
public:
    // key is the flow, value is the vertex number;
    int key, value;
};
class MaxHeap
{
public:
    MaxHeap(HeapNode *arr, int size);
    ~MaxHeap();

private:
    void FixHeap(int vertex);
    int Left(int parent_index) const;
    int Right(int parent_index) const;
    int Parent(int child_index) const;
    void Swap(HeapNode &p1, HeapNode &p2);

public:
    void IncreaseKey(int vertex, int newKey);
    bool isVertexInHeap(int vertex) const;
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
