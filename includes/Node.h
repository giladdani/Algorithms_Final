#ifndef __NODE_H
#define __NODE_H

#include <iostream>
using namespace std;

class Node
{
public:
	Node() = default;
	Node(int data, Node* next);

	const int getData() const;
	Node* DeleteAfter();

public:
	Node* next;			// @ ask Eli- what should be public and what private here?
private:
	int data;
};

#endif