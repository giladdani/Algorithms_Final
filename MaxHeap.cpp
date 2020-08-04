#include "MaxHeap.h"

// C'tor
MaxHeap::MaxHeap(HeapNode* arr, int size)
{
	heapSize = maxSize = size;
	data = arr;
	places = new int[size];
	for (int i = 0; i < size; i++)
	{
		places[i] = i;		// set every vertex's starting index in the "places array"
	}
	Build();
}

// D'tor
MaxHeap::~MaxHeap()
{
	delete data;
	delete places;
}

// Build Maximum heap according to Floyd's Algorithm
void MaxHeap::Build()
{
	for (int i = (heapSize / 2) - 1; i >= 0; i--)
		FixHeap(i);
}

// returns the location index of the vertex in the Heap's array, if not found -1 will be returned
int MaxHeap::GetIndexInHeap(int vertex) const
{
	return places[vertex - 1];
}

// Returns index of left child of parent_index in the arr
int MaxHeap::Left(int parent_index) const
{
	return (2 * parent_index + 1);
}

// Returns index of right child of parent_index in the arr
int MaxHeap::Right(int parent_index) const
{
	return (2 * parent_index + 2);
}

// Returns index of Parent of parent_index in the arr
int MaxHeap::Parent(int parent_index) const
{
	return ((parent_index - 1) / 2);
}

// Swaps the given nodes in the heap
void MaxHeap::Swap(HeapNode& p1, HeapNode& p2)
{
	// swap data
	HeapNode temp = p1;
	p1 = p2;
	p2 = temp;

	// swap places in "places array"
	int tempPlace = places[p1.value - 1];
	places[p1.value - 1] = places[p2.value - 1];
	places[p2.value - 1] = tempPlace;
}

// Returns true if the heap is empty, otherwise- return false
bool MaxHeap::IsEmpty() const
{
	if (heapSize == 0)
		return true;
	return false;
}

// Make an empty heap
void MaxHeap::MakeEmpty()
{
	heapSize = 0;
	delete data;
}

// Deletes and returns the maximum Node in the heap (by key)
HeapNode MaxHeap::DeleteMax()
{
	if (heapSize < 1)
	{
		cout << "Error: EMPTY HEAP\n";
		exit(1);
	}
	HeapNode max = data[0];
	heapSize--;
	data[0] = data[heapSize];
	FixHeap(0);

	return max;
}

// Returns the Maximum Node in the heap (by key)
HeapNode& MaxHeap::Max() const
{
	return data[0];
}

// Increase the key of the given vertex in the heap and reorders the heap accordingly
void MaxHeap::IncreaseKey(int vertex, int newKey)
{
	int placeInHeap = places[vertex - 1];		// get actual place of the vertex in the heap

	int parent = Parent(placeInHeap);
	this->data[placeInHeap].key = newKey;
	while ((placeInHeap > 0) && (data[parent].key < data[placeInHeap].key))
	{
		Swap(data[placeInHeap], data[parent]);
		placeInHeap = parent;
		parent = Parent(placeInHeap);
	}
}

// Fix Heap
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