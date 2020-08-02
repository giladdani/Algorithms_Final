#include <fstream>
#include "../../includes/FlowNetwork.h"

// Returns a Flow Network created from the input of the given file
FlowNetwork *ReadNetworkFromFile(ifstream &file)
{
	int n, m, s, t;
	int u, v, c;

	// @ add more input validations?
	file >> n; // vertices
	file >> m; // edges
	file >> s; // source
	file >> t; // sink
	if (n < 2 || m < 1 || s == t || s < 1 || t < 1)
	{
		cout << "INPUT ERROR: ABORTED!" << endl;
		exit(1);
	}
	Graph *graph = new Graph(n);

	// init capacities
	bool valid_input;
	for (int i = 0; i < m; i++)
	{
		file >> u;
		file >> v;
		file >> c;
		valid_input = graph->AddEdge(u, v, c);
		if (!valid_input)
		{
			cout << "INPUT ERROR: ABORTED!" << endl;
			exit(1);
		}
	}

	file.close();
	FlowNetwork *network = new FlowNetwork(s, t, *graph);
	delete graph;
	return network;
}

// Prints given Lists of Cuts
void PrintCuts(List &S, List &T)
{
	cout << "Min cut: S= ";
	Node *currNode = S.head;
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
