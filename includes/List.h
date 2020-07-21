#ifndef __LIST_H
#define __LIST_H

#include "Node.h"

class List
{
public:
	List();
	~List();

	void Insert(Node* newNode);

public:
	Node *head, *tail;
};

#endif