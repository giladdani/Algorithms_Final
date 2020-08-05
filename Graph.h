#ifndef __GRAPH_H
#define __GRAPH_H

#include "List.h"

class Graph
{
public:
	Graph(int size);
	Graph(const Graph &other);
	~Graph();

	void MakeEmptyGraph(int n);
	bool IsAdjacent(int u, int v);
	List* GetAdjList(int u);
	bool AddEdge(int u, int v, int c);
	void RemoveEdge(int u, int v);

	int GetSize() const;
	int GetCapacity(int u, int v) const;
	bool SetCapacity(int u, int v, int c);

private:
	int n;
	int **capacities;
};

#endif