#ifndef __UTILS_H
#define __UTILS_H

#include "FlowNetwork.h"
#include <fstream>

FlowNetwork ReadNetworkFromFile(ifstream &file);
void PrintCuts(List &S, List &T);
bool *BFS(Graph &rGraph, int s, int t, int *parent);
bool *Dijkstra(Graph &graph, int s, int *d, int *p);
void FordBFS(FlowNetwork &network);
void FordGreedy(FlowNetwork &network);

#endif