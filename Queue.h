#ifndef __QUEUE_H
#define __QUEUE_H

#include "ListNode.h"

class Queue
{
public:
	Queue();
	~Queue();

	void MakeEmpty();
	bool IsEmpty() const;
	void Enqueue(int item);
	int Dequeue();

private:
	ListNode *head, *tail;
};

#endif