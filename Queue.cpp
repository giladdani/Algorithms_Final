#include "Queue.h"

// C'tor
Queue::Queue()
{
	head = new ListNode;
	tail = head;
}

// D'tor
Queue::~Queue()
{
	MakeEmpty();
}

// Makes the queue empty
void Queue::MakeEmpty()
{
	while (head->next != NULL)
	{
		ListNode* temp = head->next;
		head->next = temp->next;
		delete temp;
	}

}

// Returns true if the queue is empty, otherwise return false
bool Queue::IsEmpty() const
{
	return (head == tail);
}

// Inserts a value into the end of the queue
void Queue::Enqueue(int item)
{
	ListNode *newNode = new ListNode(item, NULL);
	tail->next = newNode;
	tail = newNode;
}

// Removes and returns a value from the front of the queue
int Queue::Dequeue()
{
	// check if the queue is not empty
	if (IsEmpty())
	{
		cout << "Error: QUEUE EMPTY\n";
		exit(1);
	}
	ListNode *temp = head->DeleteAfter();
	int item = temp->getData();
	if (tail == temp)
		tail = head;
	delete temp;
	return item;
}