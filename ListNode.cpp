#include "List.h"

// C'tor
ListNode::ListNode(int data, ListNode *next)
{
	this->data = data;
	this->next = next;
}

// Getter
int ListNode::getData() const
{
	return data;
}

// Deletes the ListNode after this node
ListNode *ListNode::DeleteAfter()
{
	ListNode *temp = this->next;
	this->next = this->next->next;
	return temp;
}