#ifndef __FLOWNETWORK_H
#define __FLOWNETWORK_H

#include "Graph.h"

class FlowNetwork
{
public:
	FlowNetwork(int s, int t, Graph &graph); // @ pass Graph by referece?

public:
	int s, t;	 // source and sink
	Graph graph; // graph with vertices, edges and capacities
};

#endif