#include "../../includes/List.h"

List::List()
{
	head = tail = nullptr;
}

List::~List()
{
	Node *curr = head;
	Node *temp;
	while (curr != nullptr) // @ should 'next' be private? and then use Getter for it?
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
	delete curr;
}

void List::Insert(Node *newNode)
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
