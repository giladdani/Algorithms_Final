#include <fstream>
#include <string>
#include <sstream>
#include "FlowNetwork.h"

#define INVALID_VALUE -1

// Returns true of str has only Whitespaces in it
bool StringHasOnlyWhitespaces(string& str)
{
	if (str.find_first_not_of(' ') == str.npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Returns a Flow Network created from the input of the given file
FlowNetwork ReadNetworkFromFile(ifstream &file)
{
	int n, m, s, t;
	int u, v, c;
	string currentRow;
	bool isEdgeValid;

	file >> n; // vertices
	file >> m; // edges
	file >> s; // source
	file >> t; // sink

	// validate number of vertices, edges, source and sink
	if (n < 1 || m < 0 || s < 1 || t < 1 || s == t)
	{
		cout << "invalid input" << endl;
		exit(1);
	}
	
	Graph graph(n);

	// validate end of row and jump to the next
	getline(file, currentRow);
	if (!StringHasOnlyWhitespaces(currentRow))
	{
		cout << "invalid input" << endl;
		exit(1);
	}

	// read capacities
	for (int i = 0; i < m; i++)
	{
		string restOfTheRow;
		getline(file, currentRow);
		istringstream currentRowStream(currentRow);

		// if row is empty- skip to the next one
		if (StringHasOnlyWhitespaces(currentRow))
		{
			i--;
		}
		else
		{
			u = v = c = INVALID_VALUE;		// reset variables to default value (for validation purpose)
			currentRowStream >> u;
			currentRowStream >> v;
			currentRowStream >> c;

			isEdgeValid = graph.AddEdge(u, v, c);
			if (!isEdgeValid)
			{
				cout << "invalid input, edge (" << u << "," << v << ") with capacity " << c << " is not valid" << endl;
				exit(1);
			}

			currentRowStream >> restOfTheRow;
			if (!StringHasOnlyWhitespaces(restOfTheRow))
			{
				cout << "invalid input" << endl;
				exit(1);
			}
		}
	}

	// final check- validate file has no more data
	while (getline(file, currentRow))
	{
		if (!StringHasOnlyWhitespaces(currentRow))
		{
			cout << "invalid input, file contains more edges than specified/invalid data" << endl;
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
	cout << "Min cut: S = ";
	ListNode* v_node = S.head;
	while (v_node != nullptr)
	{
		cout << v_node->getData();
		if (v_node->next != nullptr)
			cout << ", ";
		else
			cout << ". ";
		v_node = v_node->next;
	}
	cout << "T = ";
	v_node = T.head;
	while (v_node != nullptr)
	{
		cout << v_node->getData();
		if (v_node->next != nullptr)
			cout << ", ";
		v_node = v_node->next;
	}
	cout << endl;
}

