#include <iostream>
#include <fstream>
#include <string.h>
#include "./includes/utils.h"
using namespace std;

int main(int argc, char *argv[])
{
	ifstream file(argv[1]);
	FlowNetwork network = ReadNetworkFromFile(file); // create Flow Network from file

	// BFS method
	cout << "BFS Method: " << endl;
	FordBFS(network);

	// Greedy method
	cout << "Greedy Method: " << endl;
	FordGreedy(network);
	return 0;
}