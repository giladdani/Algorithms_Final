#include <iostream>
#include <fstream>
#include <string.h>
#include "./includes/utils.h"
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
		cout << "File did not load successfully." << endl;
		return 0;
	}
}