#include "Graph.h"
#include "Queue.h"
#include "MaxHeap.h"
#include "utils.h"

#define MAX_INT 0x7FFFFFFF  //Biggest Signed positive integer

/* Returns a boolean visited array indicating the reachable vertices from source 's'
 in the graph and creates parents array */
bool* BFS(Graph &rGraph, int s, int t, int *parent)
{
	// allocate visited array and init all to false
	bool* visited = new bool[rGraph.n];
	for (int i = 1; i < rGraph.n; i++)
	{
		visited[i] = false;
	}

	// travel the graph with BFS using a Queue
	Queue* Q = new Queue();
	visited[s] = true;
	parent[s] = 0;
	Q->Enqueue(s);

	while (!Q->IsEmpty())
	{
		int u = Q->Dequeue();
		for (int v = 1; v < rGraph.n; v++)
		{
			// enqueue and mark all of the current vertex's neighbour that haven't been visited yet
			if (rGraph.capacities[u][v] > 0 && visited[v] == false)
			{
				visited[v] = true;
				parent[v] = u;
				Q->Enqueue(v);
			}
		}
	}
	delete Q;
	return visited;
}

/* Ford-Fulkerson BFS Method
   Prints the maximum flow of the network, the MinCut and the number of BFS iterations
   used for finding an improving path */
void FordBFS(FlowNetwork &network)
{
	int u, v;
	int maxFlow = 0;
	int itr_count = 0;
	List* S = new List();
	List* T = new List();

	// create residual graph
	Graph* rGraph = new Graph(network.graph);

	// this array will be used to retrace the potential path found by BFS
	int* parent = new int[rGraph->n];

	// if an improving path exists- find it's residual capacity and increase flow in it
	bool* visited = BFS(*rGraph, network.s, network.t, parent);
	while (visited[network.t] == true)
	{
		// count iteration
		itr_count++;

		// find the minimum value(capacity) to add to the path's flow
		int minCapacity = rGraph->capacities[parent[network.t]][network.t];
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			if (rGraph->capacities[u][v] < minCapacity)
				minCapacity = rGraph->capacities[u][v];
		}

		/* go from the end of the path to it's beginning
		   and update residual capacities in the residual graph */
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			rGraph->capacities[u][v] -= minCapacity; // reduce capacity of edge
			rGraph->capacities[v][u] += minCapacity; // increase capacity of anti-symmetric edge
		}
		maxFlow += minCapacity;

		delete[] visited; // deallocate previous array.
		visited = BFS(*rGraph, network.s, network.t, parent); // search path for next iteration
	}

	// find minCut according to last BFS iteration
	for (int i = 1; i < rGraph->n; i++)
	{
		if (visited[i] == true)
			S->Insert(new ListNode(i, nullptr));
		else
			T->Insert(new ListNode(i, nullptr));
	}

	// print
	cout << "Max flow = " << maxFlow << endl;
	PrintCuts(*S, *T);
	cout << "Number of iterations: " << itr_count << endl;
	delete rGraph;
	delete S;
	delete T;
}

/*This variation of Dijkstra algorithem finds the Biggest weighted path to every vertex.
	Changes made from the original Smallest weighted algorithem to achieve the wanted
	 output: Every vertex starting weight is 0 except s which has infinity.
		in case of using Relax,the algorithem checks if d[u] is infinity.
		 if infinity is the case, it doesn't add d[u] value.*/
bool* Dijkstra(Graph &graph, int s, int *d, int *p)
{
	bool* visited = new bool[graph.n];

	for (int i = 1; i < graph.n; i++)
	{
		visited[i] = false;
		d[i] = 0;
	}

	p[s] = 0;
	d[s] = MAX_INT; // Assume MAX_INT is infinity.
	visited[s] = true;

	HeapNode* heapNodes = new HeapNode[graph.n - 1];
	for (int i = 0; i < graph.n - 1; i++)
	{
		heapNodes[i].key = d[i + 1];
		heapNodes[i].value = i + 1;
	}

	MaxHeap Q(heapNodes, graph.n - 1);		// create Priority Queue
	HeapNode u_heapNode;
	int u;

	// Start clearing the Queue, Relaxing along the way
	while (!Q.IsEmpty())
	{
		u_heapNode = Q.DeleteMax();
		u = u_heapNode.value;
		List* adList = graph.GetAdjList(u);
		ListNode* v_node = adList->head;

		while (v_node != nullptr)
		{
			int v = v_node->getData();

			// if Relax needed
			if (((d[u] > d[v]) && (graph.capacities[u][v] > d[v])) || d[u] == MAX_INT)
			{
				if (graph.capacities[u][v] < d[u])
				{
					d[v] = graph.capacities[u][v];
				}
				else
				{
					d[v] = d[u];
				}
				visited[v] = true;
				p[v] = u;
				Q.IncreaseKey(v, d[v]);
			}
			v_node = v_node->next;
		}
		delete adList;
	}
	return visited;
}

/* Ford-Fulkerson Greedy Method
   Prints the maximum flow of the network, the MinCut and the number of BFS iterations
   used for finding an improving path */
void FordGreedy(FlowNetwork& network)
{
	int u, v;
	int maxFlow = 0;
	int itr_count = 0;
	List* S = new List();
	List* T = new List();

	// create residual graph
	Graph* rGraph = new Graph(network.graph);

	// this array will be used to retrace the potential path found by BFS
	int* parent = new int[rGraph->n];
	int* d = new int[rGraph->n];
	bool* visited = Dijkstra(*rGraph, network.s, d, parent);
	while (visited[network.t] == true)
	{
		// count iteration
		itr_count++;

		// find the minimum value(capacity) to add to the path's flow
		int minCapacity = rGraph->capacities[parent[network.t]][network.t];
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			if (rGraph->capacities[u][v] < minCapacity)
				minCapacity = rGraph->capacities[u][v];
		}

		/* go from the end of the path to it's beginning
		   and update residual capacities in the residual graph */
		for (v = network.t; v != network.s; v = parent[v])
		{
			u = parent[v];
			rGraph->capacities[u][v] -= minCapacity; // reduce capacity of edge
			rGraph->capacities[v][u] += minCapacity; // increase capacity of anti-symmetric edge
		}
		maxFlow += minCapacity;

		
		delete[] visited;	// deallocate previous array.
		visited = Dijkstra(*rGraph, network.s, d, parent);	// search path for next iteration
	}

	// find minCut according to last iteration
	for (int i = 1; i < rGraph->n; i++)
	{
		if (visited[i] == true)
			S->Insert(new ListNode(i, nullptr));
		else
			T->Insert(new ListNode(i, nullptr));
	}

	// print
	cout << "Max flow = " << maxFlow << endl;
	PrintCuts(*S, *T);
	cout << "Number of iterations: " << itr_count << endl;
	delete rGraph;
	delete S;
	delete T;
}