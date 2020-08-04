#ifndef __LIST_H
#define __LIST_H

#include "ListNode.h"

class List
{
public:
	List();
	~List();

	void Insert(ListNode* newNode);

public:
	ListNode *head, *tail;
};

#endif