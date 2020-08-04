#include "List.h"

List::List()
{
	head = tail = nullptr;
}

List::~List()
{
	ListNode* curr = head;
	ListNode* temp;
	while (curr != nullptr)
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
}

void List::Insert(ListNode* newNode)
{
	if (head == nullptr)
	{
		head = tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}
