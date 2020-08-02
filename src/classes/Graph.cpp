#include "../../includes/Graph.h"

// C'tor
Graph::Graph(int size)
{
	// we set the capacity matrix's size to be n+1 because we want it to start from index 1 and not 0
	n = size + 1;
	capacities = new int *[n];
	for (int i = 0; i < n; i++)
	{
		capacities[i] = new int[n];
		for (int j = 0; j < n; j++)
			capacities[i][j] = 0;
	}
}

// Copy c'tor
Graph::Graph(const Graph &other)
{
	this->n = other.n;
	this->capacities = new int *[n];
	for (int i = 0; i < n; i++)
	{
		capacities[i] = new int[n];
		for (int j = 0; j < n; j++)
			capacities[i][j] = other.capacities[i][j];
	}
}

// D'tor
Graph::~Graph()
{
	for (int i = 0; i < n; i++)
		delete[] capacities[i];
	delete[] capacities;
}

// Returns true if there is an Edge (u,v) in the graph, otherwise- return false
bool Graph::IsAdjacent(int u, int v)
{
	if (capacities[u][v] > 0)
		return true;
	return false;
}

// Returns a List of neighbour of 'u'
List *Graph::GetAdjList(int u)
{ //Need to built
	List *neighbour = new List();
	for (int i = 1; i < this->n; i++)
	{
		if (this->IsAdjacent(u, i))
			neighbour->Insert(new Node(i, nullptr));
	}

	return neighbour;
}

// Adds an Edge (u,v) to the graph with a positive capacity 'c'
bool Graph::AddEdge(int u, int v, int c)
{
	// validate given capacity
	if (c <= 0 || this->capacities[u][v] != 0 || u == v || u < 0 || v < 0)
		return false;
	else
	{
		capacities[u][v] = c;
		return true;
	}
}

// Removes the Edge (u,v) from the graph by assigning capacity to 0
void Graph::RemoveEdge(int u, int v)
{
	capacities[u][v] = 0;
}
