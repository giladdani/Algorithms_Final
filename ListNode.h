#ifndef __LISTNODE_H
#define __LISTNODE_H

#include <iostream>
using namespace std;

class ListNode
{
public:
	ListNode() = default;
	ListNode(int data, ListNode* next);

	int getData() const;
	ListNode* DeleteAfter();

public:
	ListNode* next;
private:
	int data;
};

#endif