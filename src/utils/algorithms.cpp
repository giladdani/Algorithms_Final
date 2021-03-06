#include "../../includes/Graph.h"
#include "../../includes/Queue.h"
#include "../../includes/MaxHeap.h"
#include "../../includes/utils.h"
#define MAX_INT 0x7FFFFFFF //Biggest Signed positive integer.

/* Returns a boolean visited array indicating the reachable vertices from source 's'
 in the graph and creates parents array */
bool *BFS(Graph &rGraph, int s, int t, int *parent)
{
	// allocate visited array and init all to false
	bool *visited = new bool[rGraph.n];
	for (int i = 1; i < rGraph.n; i++)
		visited[i] = false;

	// traverse the graph with BFS using a Queue
	Queue *Q = new Queue();
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
bool *Dijkstra(Graph &graph, int s, int *d, int *p)
{
	/*This Dijkstra algorithem finds the Biggest weighted route in the Graph.
	Changes made from the original Smallest weighted algorithem to achieve the wanted
	 output: Every vertex starting weight is 0 except s which has infinity.
	 	in case of using Relax,the algorithem checks if d[u] is infinity.
		 if infinity is the case, it doesn't add d[u] value.*/
	bool *visited = new bool[graph.n];
	for (int i = 1; i < graph.n; i++)
		visited[i] = false;
	for (int i = 1; i < graph.n; i++)
	{
		d[i] = 0;
	}
	p[s] = 0;
	d[s] = MAX_INT; //Assume MAX_INT is infinity.
	HeapNode *heapNodes = new HeapNode[graph.n - 1];
	for (int i = 0; i < graph.n - 1; i++)
	{
		heapNodes[i].key = d[i + 1];
		heapNodes[i].value = i + 1;
	}
	MaxHeap Q(heapNodes, graph.n - 1);
	while (!Q.IsEmpty())
	{
		HeapNode u = Q.DeleteMax();
		List *adList = graph.GetAdjList(u.value);
		Node *v = adList->head;
		while (v != nullptr)
		{
			int v_data = v->getData();
			if (((d[v_data] < d[u.value]) && (graph.capacities[u.value][v_data] > d[v_data]) && Q.isVertexInHeap(v_data)) || d[u.value] == MAX_INT)
			{
				d[v_data] = min(graph.capacities[u.value][v_data], d[u.value]);
				visited[v_data] = true;
				p[v_data] = u.value;
				Q.IncreaseKey(v_data, d[v_data]);
			}
			v = v->next;
		}
		delete adList;
	}
	delete[] heapNodes;
	return visited;
}

/* Prints the maximum flow of the network, the MinCut and the number of BFS iterations
   used for finding an improving path */
void FordBFS(FlowNetwork &network)
{
	int u, v;
	int maxFlow = 0;
	int itr_count = 0;
	List *S = new List();
	List *T = new List();
	// create residual graph
	Graph *rGraph = new Graph(network.graph);

	// this array will be used to retrace the potential path found by BFS
	int parent[rGraph->n];

	// if an improved path exists- increase flow in it
	bool *visited = BFS(*rGraph, network.s, network.t, parent); // @ source and sink should belong to network or graph?
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
		// search path for next iteration
		delete[] visited; //dellocate previous array.
		visited = BFS(*rGraph, network.s, network.t, parent);
	}

	// find minCut according to last BFS iteration
	for (int i = 1; i < rGraph->n; i++)
	{
		if (visited[i] == true)
			S->Insert(new Node(i, nullptr));
		else
			T->Insert(new Node(i, nullptr));
	}

	// print
	cout << "Max flow = " << maxFlow << endl;
	PrintCuts(*S, *T);
	cout << "Number of iterations: " << itr_count << endl;
	delete rGraph;
	delete S;
	delete T;
}
void FordGreedy(FlowNetwork &network)
{
	int u, v;
	int maxFlow = 0;
	int itr_count = 0;
	List *S = new List();
	List *T = new List();
	// create residual graph
	Graph *rGraph = new Graph(network.graph);

	// this array will be used to retrace the potential path found by BFS
	int parent[rGraph->n];
	int d[rGraph->n];
	bool *visited = Dijkstra(*rGraph, network.s, d, parent);
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
		// search path for next iteration
		delete[] visited; //dellocate previous array.
		visited = Dijkstra(*rGraph, network.s, d, parent);
	}
	for (int i = 1; i < rGraph->n; i++)
	{
		if (visited[i] == true)
			S->Insert(new Node(i, nullptr));
		else
			T->Insert(new Node(i, nullptr));
	}

	// print
	cout << "Max flow = " << maxFlow << endl;
	PrintCuts(*S, *T);
	cout << "Number of iterations: " << itr_count << endl;
	delete rGraph;
	delete S;
	delete T;
}