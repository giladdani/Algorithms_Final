#include "MaxHeap.h"

// Build heap (according to floyd's algorithm)
MaxHeap::MaxHeap(HeapNode *arr, int size)
{
    heapSize = maxSize = size;
    data = arr;

    for (int i = (size / 2) - 1; i >= 0; i--) // floyd's algorithm
        FixHeap(i);
}

// d'tor
MaxHeap::~MaxHeap()
{
    delete data;
}

// get index of left child of parent_index in the arr
int MaxHeap::Left(int parent_index) const
{
    return (2 * parent_index + 1);
}

// get index of right child of parent_index in the arr
int MaxHeap::Right(int parent_index) const
{
    return (2 * parent_index + 2);
}

// get index of Parent of parent_index in the arr
int MaxHeap::Parent(int parent_index) const
{
    return ((parent_index - 1) / 2);
}

// Swap
void MaxHeap::Swap(HeapNode &p1, HeapNode &p2)
{
    HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}

// IsEmpty
bool MaxHeap::IsEmpty() const
{
    if (heapSize == 0)
        return true;
    return false;
}

// MakeEmpty
void MaxHeap::MakeEmpty()
{
    heapSize = 0;
    delete data;
}

// DeleteMax
HeapNode MaxHeap::DeleteMax()
{
    if (heapSize < 1)
    {
        std::cout << "Error: EMPTY HEAP\n";
        exit(1);
    }

    HeapNode max = data[0];
    heapSize--;
    data[0] = data[heapSize];
    FixHeap(0);

    return max;
}

// Insert
void MaxHeap::Insert(HeapNode &p)
{
    if (heapSize == maxSize)
    {
        std::cout << "Error: HEAP FULL!\n";
        exit(1);
    }
    int i = heapSize;
    heapSize++;
    while ((i > 0) && (data[Parent(i)].key < p.key))
    {
        data[i] = data[Parent(i)];
        i = Parent(i);
    }
    data[i] = p;
}

// Max
HeapNode &MaxHeap::Max() const
{
    return data[0];
}

// Fix Heap Theta(log(n))
void MaxHeap::FixHeap(int parent_index)
{
    int max = parent_index;
    int left = Left(parent_index);   // get left child
    int right = Right(parent_index); // get right child

    if ((left < heapSize) && (data[parent_index].key < data[left].key))
        max = left;
    else if ((right < heapSize) && (data[max].key < data[right].key))
        max = right;
    if (max != parent_index)
    {
        Swap(data[parent_index], data[max]);
        FixHeap(max);
    }
}