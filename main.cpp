#include <iostream> 
#include <fstream>
#include <string.h>
#include "Queue.h"
#include "FlowNetwork.h"
using namespace std;

// -------------------------------- AUXILIARY FUNCTIONS -------------------------------

// Returns a Flow Network created from the input of the given file
FlowNetwork ReadNetworkFromFile(ifstream& file)
{
	int n, m, s, t;
	int u, v, c;
	
	// @ add more input validations?
	file >> n;	// vertices
	file >> m;	// edges
	file >> s;	// source
	file >> t;	// sink

	Graph graph(n);

	// init capacities
	bool valid_input;
	for (int i = 0; i < m; i++)
	{
		file >> u;
		file >> v;
		file >> c;
		valid_input = graph.AddEdge(u, v, c);
		if (!valid_input)
		{
			cout << "INPUT ERROR: edge " << "(" << u << "," << v << ") capacity must be non-negative\n";
			exit(1);
		}
	}

	file.close();
	FlowNetwork network(s, t, graph);
	return network;
}

// Prints given Lists of Cuts
void PrintCuts(List& S, List& T)
{
	cout << "Min cut: S= ";
	Node* currNode = S.head;
	while (currNode != NULL)
	{
		cout << currNode->getData();
		if (currNode->next != NULL)
			cout << ", ";
		else
			cout << ". ";
		currNode = currNode->next;
	}
	cout << "T= ";
	currNode = T.head;
	while (currNode != NULL)
	{
		cout << currNode->getData();
		if (currNode->next != NULL)
			cout << ", ";
		currNode = currNode->next;
	}
	cout << endl;
}

//---------------------------------- ALGORITHMS ----------------------------------------

/* Returns a boolean visited array indicating the reachable vertices from source 's'
 in the graph and creates parents array */
bool* BFS(Graph &rGraph, int s, int t, int* parent)
{
	// allocate visited array and init all to false
	bool* visited = new bool[rGraph.n];
	for (int i = 1; i < rGraph.n; i++)
		visited[i] = false;

	// traverse the graph with BFS using a Queue
	Queue q;
	visited[s] = true;
	parent[s] = 0;
	q.Enqueue(s);

	while (!q.IsEmpty())
	{
		int u = q.Dequeue();

		for (int v = 1; v < rGraph.n; v++)
		{
			// enqueue and mark all of the current vertex's neighbours that haven't been visited yet
			if (rGraph.capacities[u][v] > 0 && visited[v] == false)
			{
				visited[v] = true;
				parent[v] = u;
				q.Enqueue(v);
			}
		}
	}
	return visited;
}

/* Prints the maximum flow of the network, the MinCut and the number of BFS iterations
   used for finding an improving path */
void FordBFS(FlowNetwork &network)
{
	int u, v;
	int maxFlow = 0;
	int itr_count = 0;
	List S, T;

	// create residual graph
	Graph rGraph(network.graph);

	// this array will be used to retrace the potential path found by BFS
	int* parent = new int[rGraph.n];

	// if an improvmed path exists- increase flow in it
	bool* visited = BFS(rGraph, network.s, network.t, parent); // @ source and sink should belong to network or graph?
	while (visited[network.t] == true)		
	{
		// count iteration
		itr_count++;

		// find the minimum value(capacity) to add to the path's flow
		int minCapacity = rGraph.capacities[parent[network.t]][network.t];
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			if (rGraph.capacities[u][v] < minCapacity)
				minCapacity = rGraph.capacities[u][v];
		}

		/* go from the end of the path to it's beginning
		   and update residual capacities in the residual graph */
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			rGraph.capacities[u][v] -= minCapacity;	// reduce capacity of edge
			rGraph.capacities[v][u] += minCapacity;	// increase capcatiy of anti-simetric edge
		}
		maxFlow += minCapacity;
		
		// search path for next iteration
		visited = BFS(rGraph, network.s, network.t, parent);
	}

	// find minCut according to last BFS iteration
	for (int i = 1; i < rGraph.n; i++)
	{
		if (visited[i] == true)
			S.Insert(new Node(i, NULL));
		else
			T.Insert(new Node(i, NULL));
	}

	// print
	cout << "Max flow = " << maxFlow << endl;
	PrintCuts(S, T);
	cout << "Number of iterations: " << itr_count << endl;
}

/* Prints the maximum flow of the network, the MinCut and the number of iterations
   used for finding an improving path */
void FordGreedy(FlowNetwork& network)
{
	// @ FINISH
}

// -------------------------------------- MAIN ------------------------------------------
void main(int argc, char* argv[])
{
	ifstream file(argv[1]);
	FlowNetwork network = ReadNetworkFromFile(file);	// create Flow Network from file
	
	// BFS method
	cout << "BFS Method: " << endl;
	FordBFS(network);

	// Greedy method
	cout << "Greedy Method: " << endl;
	FordGreedy(network);
}