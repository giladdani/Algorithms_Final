/* Instructions:
	The user must supply the name of a text file in the Main function's argv[1].
	The program will then read the Network from the given file.
	Keep in mind that the text file must be written in the right format:
	- all parameters must be included and in the right amount.
	- source and sink cannot be the same vertex.
	- each one of the m edges with capacities parameters must be in it's own row.
	- only numbers are allowed.
	- whitespaces are allowed, they are just being ignored.
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
		cout << "File didn't load successfully. Exiting program." << endl;
		exit(1);
	}
}