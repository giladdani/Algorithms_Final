#include "Graph.h"

// C'tor
Graph::Graph(int size)
{
	// we set the capacity matrix's size to be size+1 because we want it to start from index 1 and not 0
	n = size + 1;
	capacities = new int*[n];
	for (int i = 0; i < n; i++)
	{
		capacities[i] = new int[n];
		for (int j = 0; j < n; j++)
			capacities[i][j] = 0;
	}
}

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
		delete capacities[i];
	delete capacities;
}

// creates an empty graph with n vertices
void Graph::MakeEmptyGraph(int n)
{
	// if graph already exists- delete it
	if (this->n > 0)
	{
		for (int i = 0; i < n; i++)
			delete capacities[i];
		delete capacities;
	}
	// we set the capacity matrix's size to be size+1 because we want it to start from index 1 and not 0
	this->n = n + 1;
	capacities = new int*[n];
	for (int i = 0; i < n; i++)
	{
		capacities[i] = new int[n];
		for (int j = 0; j < n; j++)
			capacities[i][j] = 0;
	}
}

// Returns true if there is an Edge (u,v) in the graph, otherwise- return false
bool Graph::IsAdjacent(int u, int v)
{
	// invalid vertices
	if (u < 1 || v < 1 || u >= n || v >= n)
	{
		return false;
	}
	else
	{
		if (capacities[u][v] > 0)
			return true;
		return false;
	}
}

// Returns a List of neighbour of 'u'
List* Graph::GetAdjList(int u)
{
	List* neighbour = new List();

	// invalid vertex
	if (u < 1 || u >= n)
	{
		return neighbour;
	}
	else
	{
		for (int i = 1; i < this->n; i++)
		{
			if (this->IsAdjacent(u, i))
				neighbour->Insert(new ListNode(i, nullptr));
		}
	}
	return neighbour;
}

// Adds an Edge (u,v) to the graph with a positive capacity 'c'
bool Graph::AddEdge(int u, int v, int c)
{
	if (c <= 0)					// validate positive capacity
	{
		return false;
	}
	if ((u < 1) || (u >= n) || (v < 1) || (v >= n))	// validate vertices in range 1 to n
	{
		return false;
	}
	if (u == v)					// validate no self-loop
	{
		return false;
	}
	if (capacities[u][v] > 0)	// validate edge doesn't exists yet (no parallel edges)
	{
		return false;
	}

	capacities[u][v] = c;
	return true;
}

// Removes the Edge (u,v) from the graph by assigning capacity to 0
void Graph::RemoveEdge(int u, int v)
{
	capacities[u][v] = 0;
}

// Returns the number of vertices in the graph
int Graph::GetSize() const
{
	return n;
}

// Returns the capacity of the edge (u,v)
int Graph::GetCapacity(int u, int v) const
{
	// invalid vertices
	if ((u < 1) || (u >= n) || (v < 1) || (v >= n))
	{
		return (-1);
	}
	else
	{
		return capacities[u][v];
	}
}

// Sets the capacity of edge (u,v) to c
bool Graph::SetCapacity(int u, int v, int c)
{
	// invalid vertices or new capacity
	if ((u < 1) || (u >= n) || (v < 1) || (v >= n) || c < 0)
	{
		return false;
	}
	else
	{
		capacities[u][v] = c;
	}
}