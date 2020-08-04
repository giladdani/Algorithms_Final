/* Instructions:
	The Program recives a text file as input (passed as parameter to the main) describing a Graph with source
	and sink vertices and capacities of existing edges.
	The program will then create a Flow Network and calculate and print the maximum flow and minimum cut
	of the network in 2 implementations of Ford-Fulkerson:
	1) Using BFS to find the improving path each iteration.
	2) Using a "greedy" variation of Dijkstra to find the "most improving" path each iteration.
	
	Keep in mind that the text file must be written in the right format.
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include "utils.h"
using namespace std;

int main(int argc, char *argv[])
{
	ifstream file(argv[1], ios::in);
	if (file)
	{
		FlowNetwork network = ReadNetworkFromFile(file); // create Flow Network from file

		// BFS method
		cout << "BFS Method: " << endl;
		FordBFS(network);

		// Greedy method
		cout << "Greedy Method: " << endl;
		FordGreedy(network);
		return 0;
	}
	else
	{
		cout << "File didn't load successfully, ABORTED." << endl;
		exit(1);
	}
}