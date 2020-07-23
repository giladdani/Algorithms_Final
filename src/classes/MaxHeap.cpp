#include "../../includes/MaxHeap.h"

// Build heap (according to floyd's algorithm)
MaxHeap::MaxHeap(HeapNode *arr, int size)
{
    heapSize = maxSize = size;
    this->data = new HeapNode[size];
    for (int i = 0; i < size; i++)
        this->data[i] = arr[i];
    for (int i = (size / 2) - 1; i >= 0; i--) // floyd's algorithm
        FixHeap(i);
}

// d'tor
MaxHeap::~MaxHeap()
{
    delete[] this->data;
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
    };
    data[i] = p;
}

// Max
HeapNode &MaxHeap::Max() const
{
    return data[0];
}
void MaxHeap::IncreaseKey(int vertex, int newKey)
{
    int placeInHeap;
    for (int i = 0; i < this->heapSize; i++)
    //Finding actually place of the vertex in the Heap
    {
        if (this->data[i].value == vertex)
            placeInHeap = i;
    }
    int parent = Parent(placeInHeap);
    this->data[placeInHeap].key = newKey;
    while ((placeInHeap > 0) && (data[parent].key < data[placeInHeap].key))
    {
        Swap(data[placeInHeap], data[parent]);
        placeInHeap = parent;
        parent = Parent(placeInHeap);
    }
}
bool MaxHeap::isVertexInHeap(int vertex) const
{
    for (int i = 0; i < this->heapSize; i++)
    {
        if (this->data[i].value == vertex)
            return true;
    }
    return false;
}

// Fix Heap Theta(log(n))
void MaxHeap::FixHeap(int vertex)
{
    int max = vertex;
    int left = Left(vertex);   // get left child
    int right = Right(vertex); // get right child

    if ((left < heapSize) && (data[vertex].key < data[left].key))
        max = left;
    else if ((right < heapSize) && (data[max].key < data[right].key))
        max = right;
    if (max != vertex)
    {
        Swap(data[vertex], data[max]);
        FixHeap(max);
    }
}