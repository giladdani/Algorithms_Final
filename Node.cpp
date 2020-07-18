#include "Node.h"

// C'tor
Node::Node(int data, Node* next)
{
	this->data = data;
	this->next = next;
}

// Getter
const int Node::getData() const
{
	return data;
}

// Deletes the Node after this node
Node* Node::DeleteAfter()
{
	Node* temp = this->next;
	this->next = this->next->next;
	return temp;
}