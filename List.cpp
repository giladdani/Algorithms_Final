#include "List.h"

List::List()
{
	head = tail = NULL;
}

List::~List()
{
	Node* curr = head;
	Node* temp;
	while (curr->next != NULL)			// @ should 'next' be private? and then use Getter for it?
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
	delete curr;
}

void List::Insert(Node* newNode)
{
	if (head == NULL)
	{
		head = tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}